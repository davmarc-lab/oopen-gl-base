#include "SpotLight.hpp"

SpotLight::SpotLight(vec3 position, vec3 direction, float cutOff)
{
    this->position = position;
    this->direction = direction;
    this->cutOff = cutOff;
}

void SpotLight::drawLight(Shader shader)
{
    // Set shader type for spot lights
    shader.use();

    shader.setInt("lightType", LightType::SPOTLIGHT);

    shader.setVec3("light.position", this->position);
    shader.setVec3("light.direction", this->direction);
    shader.setFloat("light.cutOff", this->cutOff);

    shader.setVec3("light.ambient", this->ambient);
    shader.setVec3("light.diffuse", this->diffuse);
    shader.setVec3("light.specular", this->specular);
}
