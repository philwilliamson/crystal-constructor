#include <crystal_constructor/opengl_graphics/ebo.h>

namespace crystal_constructor{ namespace opengl_graphics {

EBO::EBO(std::vector<GLuint>& indices)
{
    glGenBuffers(1, &ID_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void EBO::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_);
}

void EBO::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() const
{
    glDeleteBuffers(1, &ID_);
}

}} // class for handling an OpenGL element buffer object