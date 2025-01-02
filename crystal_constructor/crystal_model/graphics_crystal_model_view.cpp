#include <crystal_constructor/crystal_model/graphics_crystal_model_view.h>

namespace crystal_constructor{ namespace crystal_model {

GraphicsCrystalModelView::GraphicsCrystalModelView(const CrystalModel& crystalModel) : crystalModel_{crystalModel} {};

crystal_constructor::opengl_graphics::MeshData GraphicsCrystalModelView::GetCellMeshData() const
{
    glm::mat3 basisChangeMatrix{
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    };
    
    Vector3 a_hat = crystalModel_.GetAHat();
    glm::vec3 a_hat_local = basisChangeMatrix * glm::vec3{a_hat.x, a_hat.y, a_hat.z};
    
    Vector3 b_hat = crystalModel_.GetBHat();
    glm::vec3 b_hat_local = basisChangeMatrix * glm::vec3{b_hat.x, b_hat.y, b_hat.z};
    
    Vector3 c_hat = crystalModel_.GetCHat();
    glm::vec3 c_hat_local = basisChangeMatrix * glm::vec3{c_hat.x, c_hat.y, c_hat.z};

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
    
    crystal_constructor::opengl_graphics::MeshData cellMeshData{verts, inds};

    return cellMeshData;
}

glm::mat4  GraphicsCrystalModelView::GetModelMatrix() const
{
    Vector3 modelAHat{crystalModel_.GetAHat()};
    Vector3 modelBHat{crystalModel_.GetBHat()};
    Vector3 modelCHat{crystalModel_.GetCHat()};

    glm::vec3 aHat{modelAHat.x, modelAHat.y, modelAHat.z};
    glm::vec3 bHat{modelBHat.x, modelBHat.y, modelBHat.z};
    glm::vec3 cHat{modelCHat.x, modelCHat.y, modelCHat.z};

    glm::vec3 diagonal = aHat + bHat + cHat;

    float scaleFactor = std::sqrt(3.0f) / glm::length(diagonal);

    glm::mat4 modelMatrix
    {
        glm::vec4{scaleFactor, 0.0f, 0.0f, 0.0f},
        glm::vec4{0.0f, scaleFactor, 0.0f, 0.0f},
        glm::vec4{0.0f, 0.0f, scaleFactor, 0.0f},
        glm::vec4{0.0f, 0.0f, 0.0f, 1.0f},
    };

    return modelMatrix;
}

const std::vector<AtomDrawData> GraphicsCrystalModelView::GetAtomsUniformData() const
{
    std::vector<AtomDrawData> atomDrawData{};

    glm::mat3 basisChangeMatrix{
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    };

    Vector3 aHat{crystalModel_.GetAHat()};
    glm::vec3 aHatLocal{basisChangeMatrix * glm::vec3{aHat.x, aHat.y, aHat.z}};
    Vector3 bHat{crystalModel_.GetBHat()};
    glm::vec3 bHatLocal{basisChangeMatrix * glm::vec3{bHat.x, bHat.y, bHat.z}};
    Vector3 cHat{crystalModel_.GetCHat()};
    glm::vec3 cHatLocal{basisChangeMatrix * glm::vec3{cHat.x, cHat.y, cHat.z}};

    glm::mat4 offsetMatrix{
        glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
        glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
        glm::vec4((aHatLocal + bHatLocal + cHatLocal) * -0.5f, 1.0f)
    };

    glm::mat4 scaleMatrix{GetModelMatrix()};

    const std::vector<Atom>& modelAtoms{crystalModel_.GetAtoms()};

    for (int idx = 0; idx < modelAtoms.size(); idx++)
    {
        AtomDrawData currentAtomDrawData{};
        crystal_constructor::crystal_model::Atom currentAtom{modelAtoms.at(idx)};
        currentAtomDrawData.color = glm::vec3{currentAtom.element.color[0], currentAtom.element.color[1], currentAtom.element.color[2]};

        glm::vec3 atomPosition{
            currentAtom.position.x * glm::vec3(aHat.x, aHat.y, aHat.z)
            + currentAtom.position.y * glm::vec3(bHat.x, bHat.y, bHat.z)
            + currentAtom.position.z * glm::vec3(cHat.x, cHat.y, cHat.z)
        };

        atomPosition = basisChangeMatrix * atomPosition;
        
        glm::mat4 positionMatrix{
            glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
            glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
            glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
            glm::vec4(atomPosition, 1.0f)
        };

        currentAtomDrawData.modelMatrix = scaleMatrix * positionMatrix * offsetMatrix;

        atomDrawData.push_back(currentAtomDrawData);
    }
    
    return atomDrawData;
}

}} // class for getting mesh data based on crystal model cell