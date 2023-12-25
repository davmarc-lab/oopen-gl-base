#pragma once

#include "Light.hpp"

class SpotLight : public Light
{
    private:
        vec3 position;
        vec3 direction;
        float cutOff;

    public:
        SpotLight(vec3 position, vec3 direction, float cutOff);

        vec3 getPosition() { return this->position; }

        void setPosition(vec3 pos) { this->position = pos; }

        vec3 getDirection() { return this->direction; }

        void setDirection(vec3 dir) { this->direction = dir; }

        float getCutOff() { return this->cutOff; }

        void setCutOff(float value) { this->cutOff = value; }

        virtual void drawLight(Shader shader) override;
};
