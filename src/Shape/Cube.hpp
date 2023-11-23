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

        virtual void createVertexArray() override;

        virtual void draw(Shader shader) override;

        virtual void clearShape() override;
};
