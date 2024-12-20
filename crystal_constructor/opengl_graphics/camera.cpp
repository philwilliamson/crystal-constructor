#include <crystal_constructor/opengl_graphics/camera.h>

namespace crystal_constructor{ namespace opengl_graphics {

Camera::Camera(float aspect) : aspect_{aspect} {}

glm::mat4 Camera::GetMatrix() const
{
    glm::vec3 position = glm::vec3(
        radius_ * glm::sin(theta_) * glm::sin(phi_),
        radius_ * glm::cos(theta_),
        radius_ * glm::sin(theta_) * glm::cos(phi_)
    );

    glm::vec4 up = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
    up = glm::rotate(glm::mat4(1.0f), phi_, glm::vec3(0.0f, 1.0f, 0.0f)) * up;
    glm::vec4 right = glm::vec4(glm::cross(glm::vec3(up), glm::vec3(0.0f, 1.0f, 0.0f)), 1.0f);
    up = glm::rotate(glm::mat4(1.0f),  theta_, glm::vec3(right)) * up;
    
    glm::mat4 viewMat = glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(up));
    
    glm::mat4 projectionMat = glm::ortho(
        -1.0f * aspect_, aspect_,
        -1.0f, 1.0f,
        0.1f, 100.0f
    );

    return projectionMat * viewMat;
}

void Camera::UpdateFromInputs(GLFWwindow* window, float deltaTime)
{
    float sensitivity = baseSensitivity_ * deltaTime;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !mouseDown_)
    {
        mouseDown_ = true;
        glfwGetCursorPos(window, &mouseXInitial_, &mouseYInitial_);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        mouseDown_ = false;
    }

    if (mouseDown_)
    {
        double mouseX{}, mouseY{};
        glfwGetCursorPos(window, &mouseX, &mouseY);
        float phiDiff = sensitivity * (float)(mouseXInitial_ - mouseX);
        float thetaDiff = sensitivity * (float)(mouseYInitial_ - mouseY);

        phi_ += phiDiff;
        theta_ += thetaDiff;

        if (theta_ > glm::radians(180.0f))
        {
            theta_ = glm::radians(180.0f);
        }
        
        if (theta_ < glm::radians(0.0f))
        {
            theta_ = glm::radians(0.0f);
        }

        mouseXInitial_ = mouseX;
        mouseYInitial_ = mouseY;
    }
}

void Camera::SetAspect(float aspect)
{
    aspect_ = aspect;
}

}} // class for handling camera data
    