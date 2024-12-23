#include <crystal_constructor/crystal_model/mesh_crystal_cell_view.h>

namespace crystal_constructor{ namespace crystal_model {

MeshCrystalCellView::MeshCrystalCellView(const CrystalModel& crystalModel) : crystalModel_{crystalModel} {};

CellMeshData MeshCrystalCellView::GetCellMeshData() const
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
    
	std::vector<GLuint> inds
    {
        0, 1,
        1, 2,
        2, 3,
        3, 0,
        4, 5,
        5, 6,
        6, 7,
        7, 4,
        0, 4,
        1, 5,
        2, 6,
        3, 7,
    };
    
    CellMeshData cellMeshData{verts, inds};

    return cellMeshData;
}

}} // class for getting mesh data based on crystal model cell