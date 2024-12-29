#include <crystal_constructor/opengl_graphics/mesh.h>

namespace crystal_constructor{ namespace opengl_graphics {

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices) : vertices_{vertices}, indices_{indices}
{
    vao_.Bind();

    vbo_.Bind();
    ebo_.Bind();

    vao_.LinkAttrib(vbo_, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0); // position
    vao_.LinkAttrib(vbo_, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float))); // normal
    vao_.Unbind();
    vbo_.Unbind();
    ebo_.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera, GLenum mode) const
{
    shader.Activate();
    vao_.Bind();

    shader.UpdateUniformMatrix4fv("modelMatrix", modelMatrix_);
    shader.UpdateUniformMatrix4fv("viewMatrix", camera.GetViewMatrix());
    shader.UpdateUniformMatrix4fv("projMatrix", camera.GetProjMatrix());

    glDrawElements(mode, indices_.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::SetVertices(std::vector<Vertex>& vertices)
{
    vertices_ = vertices;
    vbo_.SetVertices(vertices);
}

void Mesh::SetModelMatrix(glm::mat4 modelMatrix)
{
    modelMatrix_ = modelMatrix;
}

}} // class for handling mesh data