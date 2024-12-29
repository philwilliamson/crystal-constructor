#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <vector>

#include <glad/glad.h>

#include <crystal_constructor/opengl_graphics/vertex.h>

namespace crystal_constructor{ namespace opengl_graphics {

struct MeshData
{
    std::vector<Vertex> vertices{};
    std::vector<GLuint> indices{};
};

}} // struct for holding mesh vertices and indices

#endif