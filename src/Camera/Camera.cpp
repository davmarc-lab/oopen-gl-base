#include "Camera.hpp"
#include <glm/ext/matrix_transform.hpp>

void Camera::setCameraPosition(vec3 pos)
{
    this->cameraPos = pos;
    this->view = glm::lookAt(this->cameraPos,
                    this->cameraPos + this->cameraFront,
                    this->cameraUp);
}

void Camera::moveCamera(vec3 position)
{
    this->setCameraPosition(position);
}
