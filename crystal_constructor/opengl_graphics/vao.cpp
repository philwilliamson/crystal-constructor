#include <crystal_constructor/opengl_graphics/vao.h>

namespace crystal_constructor{ namespace opengl_graphics {

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

GLuint VAO::GetId() const
{
    return ID;
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) const
{
    VBO.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind() const
{
    glBindVertexArray(ID);
}

void VAO::Unbind() const
{
    glBindVertexArray(0);
}

void VAO::Delete() const
{
    glDeleteVertexArrays(1, &ID);
}

}} // class for handling an OpenGL vertex array object