#include <crystal_constructor/opengl_graphics/vbo.h>

namespace crystal_constructor{ namespace opengl_graphics {

VBO::VBO(std::vector<Vertex>& vertices)
{
    glGenBuffers(1, &ID_);
    glBindBuffer(GL_ARRAY_BUFFER, ID_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void VBO::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, ID_);
}

void VBO::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() const
{
    glDeleteBuffers(1, &ID_);
}

}} // class for handling an OpenGL vertex buffer object