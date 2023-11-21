#pragma once

#include "../Lib.hpp"
#include "../Color/Color.hpp"
#include "ComplexShape3D.hpp"

#include <vector>

class Cube : public ComplexShape3D
{
    private:
        GLuint ebo;
        vector<int> indices;
        Color color;
        
        void buildCube();

    public:
        Cube(Color color);

};
