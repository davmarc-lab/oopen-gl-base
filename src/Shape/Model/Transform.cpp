#include "Transform.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

mat4 Transform::applyTransofrmation(vec3 translateVector,
        vec3 scaleVector,
        vec3 rotateAxis,
        float rotationValue)
{
    mat4 result(1.0f), translate(1.0f), scale(1.0f), rotate(1.0f);

    translate = glm::translate(translate, translateVector);
    scale = glm::scale(scale, scaleVector);

    if (rotationValue != 0)
    {
        rotation = glm::rotate(rotate, radians(0.0f), rotateAxis);
    }
    else
    {
        // rotation with quaternion
        vec3 tmp = rotateAxis * sin(rotationValue / 2);
        this->rotation = quat(tmp);
        rotate = toMat4(this->rotation);
    }

    return scale * rotate * translate;
}
