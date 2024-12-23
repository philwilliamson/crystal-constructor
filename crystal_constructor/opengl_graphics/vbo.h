#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <crystal_constructor/opengl_graphics/vertex.h>

namespace crystal_constructor{ namespace opengl_graphics {

class VBO
{
public:
    explicit VBO(std::vector<Vertex>& vertices);

    void Bind() const;
    void Unbind() const;
    void SetVertices(std::vector<Vertex>& vertices) const;
    void Delete() const;

private:
    GLuint ID_{};
};

}} // class for handling an OpenGL vertex buffer object

#endif