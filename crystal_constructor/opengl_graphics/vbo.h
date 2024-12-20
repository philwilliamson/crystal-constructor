#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace crystal_constructor{ namespace opengl_graphics {

struct Vertex
{
    glm::vec3 position{};
};

class VBO
{
public:
    explicit VBO(std::vector<Vertex>& vertices);

    GLuint GetId() const;
    
    void Bind() const;
    void Unbind() const;
    void Delete() const;

private:
    GLuint ID_{};
};

}} // class for handling an OpenGL vertex buffer object

#endif