#include <crystal_constructor/crystal_model/graphics_crystal_model_view.h>

namespace crystal_constructor{ namespace crystal_model {

GraphicsCrystalModelView::GraphicsCrystalModelView(const CrystalModel& crystalModel) : crystalModel_{crystalModel} {};

CellMeshData GraphicsCrystalModelView::GetCellMeshData() const
{
    glm::mat3 basisMatrix{
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    };
    
    Vector3 a_hat = crystalModel_.GetAHat();
    glm::vec3 a_hat_local = basisMatrix * glm::vec3{a_hat.x, a_hat.y, a_hat.z};
    
    Vector3 b_hat = crystalModel_.GetBHat();
    glm::vec3 b_hat_local = basisMatrix * glm::vec3{b_hat.x, b_hat.y, b_hat.z};
    
    Vector3 c_hat = crystalModel_.GetCHat();
    glm::vec3 c_hat_local = basisMatrix * glm::vec3{c_hat.x, c_hat.y, c_hat.z};

    std::vector<crystal_constructor::opengl_graphics::Vertex> verts
    {
        crystal_constructor::opengl_graphics::Vertex{glm::vec3{0.0f, 0.0f, 0.0f}},
        crystal_constructor::opengl_graphics::Vertex{a_hat_local},
        crystal_constructor::opengl_graphics::Vertex{b_hat_local},
        crystal_constructor::opengl_graphics::Vertex{c_hat_local},
        crystal_constructor::opengl_graphics::Vertex{a_hat_local + b_hat_local},
        crystal_constructor::opengl_graphics::Vertex{b_hat_local + c_hat_local},
        crystal_constructor::opengl_graphics::Vertex{a_hat_local + c_hat_local},
        crystal_constructor::opengl_graphics::Vertex{a_hat_local + b_hat_local + c_hat_local},
    };

    glm::mat4 translationMat{
        glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
        glm::vec4((a_hat_local + b_hat_local + c_hat_local) * -0.5f, 1.0f)
    };

    for (crystal_constructor::opengl_graphics::Vertex& vertex : verts)
    {
        vertex.position = translationMat * glm::vec4(vertex.position, 1.0f);
    }

	std::vector<GLuint> inds
    {
        0, 1,
        0, 2,
        0, 3,
        1, 4,
        2, 4,
        2, 5,
        3, 5,
        1, 6,
        3, 6,
        4, 7,
        5, 7,
        6, 7,
    };
    
    CellMeshData cellMeshData{verts, inds};

    return cellMeshData;
}

}} // class for getting mesh data based on crystal model cell