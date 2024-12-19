#include <crystal_constructor/opengl_graphics/shader.h>

namespace crystal_constructor{ namespace opengl_graphics {

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = crystal_constructor::utils::get_file_contents(vertexFile);
    std::string fragmentCode = crystal_constructor::utils::get_file_contents(fragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    buildErrors(vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    buildErrors(fragmentShader, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    buildErrors(ID, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint Shader::GetId() const
{
    return ID;
}

void Shader::Activate() const
{
    glUseProgram(ID);
}

void Shader::Delete() const
{
    glDeleteProgram(ID);
}

void Shader::buildErrors(unsigned int shader, const char* type)
{
    GLint buildSuccess;
    char infoLog[1024];
    if (type == "PROGRAM")
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &buildSuccess);
        if (buildSuccess == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &buildSuccess);
        if (buildSuccess == GL_FALSE)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        
    }
}

}} // class for handling shader programs