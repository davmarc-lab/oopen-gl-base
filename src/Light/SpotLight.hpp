#pragma once

#include "Light.hpp"

class SpotLight : public Light
{
    private:
        vec3 position;
        vec3 direction;
        float cutOff;
        float constant;
        float linear;
        float quadratic;

    public:
        SpotLight(vec3 position, vec3 direction, float cutOff);

        vec3 getPosition() { return this->position; }

        void setPosition(vec3 pos) { this->position = pos; }

        vec3 getDirection() { return this->direction; }

        void setDirection(vec3 dir) { this->direction = dir; }

        float getCutOffValue() { return this->cutOff; }

        void setCutOffValue(float value) { this->cutOff = value; }

        float getConstantValue() { return this->constant; }

        void setConstantValue(float value) { this->constant = value; }

        float getLinearValue() { return this->linear; }

        void setLinearValue(float value) { this->linear = value; }

        float getQuadraticValue() { return this->quadratic; }

        void setQuadraticValue(float value) { this->quadratic = value; }

        virtual void drawLight(Shader shader) override;
};
