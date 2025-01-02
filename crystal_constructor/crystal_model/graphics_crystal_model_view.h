#ifndef GRAPHICS_CRYSTAL_MODEL_VIEW_H
#define GRAPHICS_CRYSTAL_MODEL_VIEW_H

#include <cmath>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <crystal_constructor/crystal_model/crystal_model.h>
#include <crystal_constructor/opengl_graphics/mesh_data.h>

namespace crystal_constructor{ namespace crystal_model {

struct AtomDrawData {
    glm::vec3 color{};
    glm::mat4 modelMatrix{};
};

class GraphicsCrystalModelView
{
public:
    explicit GraphicsCrystalModelView(const CrystalModel& crystalModel);

    crystal_constructor::opengl_graphics::MeshData GetCellMeshData() const;
    glm::mat4 GetModelMatrix() const;
    const std::vector<AtomDrawData> GetAtomsUniformData() const;

private:
    const CrystalModel& crystalModel_{};
};

}} // class for getting mesh data based on crystal model cell

#endif
