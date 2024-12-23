#include <crystal_constructor/opengl_graphics/mesh.h>

namespace crystal_constructor{ namespace opengl_graphics {

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices) : vertices_{vertices}, indices_{indices}
{
    vao_.Bind();

    vbo_.Bind();
    ebo_.Bind();

    vao_.LinkAttrib(vbo_, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0); // position
    vao_.Unbind();
    vbo_.Unbind();
    ebo_.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera, GLenum mode)
{
    shader.Activate();
    vao_.Bind();

    shader.UpdateUniformMatrix4fv("camMatrix", camera.GetMatrix());

    glDrawElements(mode, indices_.size(), GL_UNSIGNED_INT, 0);
}

}} // class for handling mesh data