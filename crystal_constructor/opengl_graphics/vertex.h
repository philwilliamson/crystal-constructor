#ifndef VERTEX_CLASS_H
#define VERTEX_CLASS_H

#include <glm/glm.hpp>

namespace crystal_constructor{ namespace opengl_graphics {

struct Vertex
{
    glm::vec3 position{};
    glm::vec3 normal{};
};

}} // struct for storing vertex data

#endif