#pragma once

#include "../Lib.hpp"

class Light
{
    public:
        vec3 position;
        vec4 color;
        /* float intensity; */

        virtual void drawLight() = 0;
};
