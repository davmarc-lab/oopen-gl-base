#pragma once

#include "../Lib.hpp"

class Camera
{
    private:
        mat4 view = mat4(1.0f);
        vec3 cameraPos = vec3(0, 0, 3);
        vec3 cameraFront = vec3(0, 0, -1);
        vec3 cameraUp = vec3(0, 1, 0);
        vec3 rotation = vec3(0);

    public:
        Camera()
        {
            this->view = glm::lookAt(this->cameraPos,
                    this->cameraPos + this->cameraFront,
                    this->cameraUp);
        }

        void setViewMatrix(mat4 mat) { this->view = mat; }

        mat4 getViewMatrix() { return this->view; }

        void setCameraFront(vec3 vec) { this->cameraFront = vec; }

        vec3 getCameraFront() { return this->cameraFront; }

        vec3 getCameraUp() { return this->cameraUp; }

        // This method reset the view matrix, use only for setup.
        // If you want to move the camera use the moveCamera method.
        void setCameraPosition(vec3 pos);

        vec3 getCameraPosition() { return this->cameraPos; }

        void moveCamera(vec3 position);

        void rotateCamera(vec3 rotationAxis, float rotationValue);
};
