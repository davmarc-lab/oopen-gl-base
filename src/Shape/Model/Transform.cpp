#include "Transform.hpp"
#include <glm/gtx/quaternion.hpp>

void Transform::applyTransofrmation(vec3 translateVector,
        vec3 scaleVector,
        vec3 rotateAxis,
        float rotationValue)
{
    mat4 base = mat4(1.0f);
    mat4 translate(1.0f), scale(1.0f), rotate(1.0f);

    translate = glm::translate(base, translateVector);
    scale = glm::scale(base, scaleVector);
    if (rotateAxis == vec3(0))
    {
        rotateAxis = vec3(1);
        rotationValue = 0;
    }

    rotate = glm::rotate(rotate, radians(rotationValue), rotateAxis);

    /* if (quaternion not set) */
    /* { */
    /*     rotate = glm::rotate(rotate, radians(rotationValue), rotateAxis); */
    /* } */
    /* else */
    /* { */
    /*     // rotation with quaternion */
    /*     vec3 tmp = rotateAxis * sin(rotationValue / 2); */
    /*     this->rotation = quat(tmp); */
    /*     rotate = toMat4(this->rotation); */
    /* } */

    this->setModelMatrix(this->model * scale * rotate * translate);
}
