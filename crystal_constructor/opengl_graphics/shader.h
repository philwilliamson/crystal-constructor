#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <crystal_constructor/utils/get_file_contents.h>

namespace crystal_constructor{ namespace opengl_graphics {

class Shader
{
public:
    Shader(const char* vertexFile, const char* fragmentFile);

    GLuint GetId() const;

    void Activate() const;
    void UpdateUniformMatrix4fv(const char* name, glm::mat4 value) const;
    void Delete() const;

private:
    GLuint ID_{};

    void buildErrors(unsigned int shader, const char* type);
};

}} // class for handling shader programs

#endif