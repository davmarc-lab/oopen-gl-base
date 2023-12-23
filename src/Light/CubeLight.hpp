#pragma once

#include "Light.hpp"
#include "../Shape/Cube.hpp"

class CubeLight : public Light
{
    private:
        Cube cube = Cube(color::BLACK);

    public:
        CubeLight() {}

        CubeLight(vec3 pos, vec4 color);
        
        virtual void drawLight() override;
};
