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
    up = glm::rotate(glm::mat4(1.0f), glm::radians(phi_), glm::vec3(0.0f, 1.0f, 0.0f)) * up;
    glm::vec4 right = glm::vec4(glm::cross(glm::vec3(up), glm::vec3(0.0f, 1.0f, 0.0f)), 1.0f);
    up = glm::rotate(glm::mat4(1.0f),  glm::radians(theta_), glm::vec3(right)) * up;
    
    glm::mat4 viewMat = glm::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(up));
    
    glm::mat4 projectionMat = glm::ortho(
        -1.0f * aspect_, aspect_,
        -1.0f, 1.0f,
        0.1f, 100.0f
    );

    return projectionMat * viewMat;
}

}} // class for handling camera data
    