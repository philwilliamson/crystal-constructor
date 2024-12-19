#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include <crystal_constructor/opengl_graphics/shader.h>

namespace crystal_constructor{ namespace opengl_graphics {

class Camera
{
public:
    explicit Camera(float aspect);

    glm::mat4 GetMatrix() const;

private:
    float aspect_{};
    float theta_{90.0f};
    float phi_{0.0f};
    float radius_{2.0f};
    bool mouseDown_{false};
    float sensitivityFactor_{0.01f};
};

}} // class for handling camera data

#endif