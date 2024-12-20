#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <vector>

#include <glad/glad.h>

namespace crystal_constructor{ namespace opengl_graphics {

class EBO
{
public:
    explicit EBO(std::vector<GLuint>& indices);

    void Bind() const;
    void Unbind() const;
    void Delete() const;

private:
    GLuint ID_{};
};

}} // class for handling an OpenGL element buffer object

#endif