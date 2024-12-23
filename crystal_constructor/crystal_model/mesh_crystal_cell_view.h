#ifndef MESH_CRYSTAL_CELL_VIEW_H
#define MESH_CRYSTAL_CELL_VIEW_H

#include <vector>

#include <glad/glad.h>

#include <crystal_constructor/opengl_graphics/vertex.h>
#include <crystal_constructor/crystal_model/crystal_model.h>

namespace crystal_constructor{ namespace crystal_model {

struct CellMeshData
{
    std::vector<crystal_constructor::opengl_graphics::Vertex> vertices{};
    std::vector<GLuint> indices{};
};

class MeshCrystalCellView
{
public:
    explicit MeshCrystalCellView(const CrystalModel& crystalModel);

    CellMeshData GetCellMeshData() const;

private:
    const CrystalModel& crystalModel_{};
};

}} // class for getting mesh data based on crystal model cell

#endif
