#ifndef MESH_H
#define MESH_H

#include <vector>

#include <crystal_constructor/opengl_graphics/vao.h>
#include <crystal_constructor/opengl_graphics/ebo.h>
#include <crystal_constructor/opengl_graphics/camera.h>

namespace crystal_constructor{ namespace opengl_graphics {

class Mesh
{
public:
    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);

    void Draw(Shader& shader, Camera& camera, GLenum mode = GL_TRIANGLES);

    void SetVertices(std::vector<Vertex>& vertices);

private:
    std::vector<Vertex> vertices_{};
    std::vector<GLuint> indices_{};

    VAO vao_{};
    VBO vbo_{vertices_};
    EBO ebo_{indices_};
};

}} // class for handling mesh data

#endif