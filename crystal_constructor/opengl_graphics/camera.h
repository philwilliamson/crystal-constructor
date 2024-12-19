#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <crystal_constructor/opengl_graphics/shader.h>

namespace crystal_constructor{ namespace opengl_graphics {

class Camera
{
public:
    explicit Camera(float aspect);

    glm::mat4 GetMatrix() const;

    void UpdateFromInputs(GLFWwindow* window, float deltaTime);

private:
    float aspect_{};
    float theta_{glm::radians(90.0f)};
    float phi_{glm::radians(0.0f)};
    float radius_{2.0f};
    bool mouseDown_{false};
    float baseSensitivity_{0.2f};
    double mouseXInitial_{};
    double mouseYInitial_{};
};

}} // class for handling camera data

#endif