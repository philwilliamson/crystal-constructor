#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include <crystal_constructor/opengl_graphics/vbo.h>

namespace crystal_constructor{ namespace opengl_graphics {

class VAO
{
public:
    VAO();

    GLuint GetId() const;

    void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) const;
    void Bind() const;
    void Unbind() const;
    void Delete() const;

private:
    GLuint ID_{};
};

}} // class for handling an OpenGL vertex array object

#endif