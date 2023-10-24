#pragma once

#include "../Lib.hpp"
#include "../Shape/Shape.hpp"

class ComplexShape2D : protected Shape2D
{
private:
    GLuint ebo_indexes;
    vector<vec3> controls;
    int intPoints;
    int fragmentType;

public:
    ComplexShape2D::ComplexShape2D(int ntriangle, vector<vec3> vertex,
                                   vector<vec4> colors, GLuint ebo, mat4 model,
                                   vector<vec3> controls, int intPoints, int fragmentType);

    ComplexShape2D::ComplexShape2D();

    void addControlPoints(vec3 elem) { this->controls.push_back(elem); }

    vector<vec3> getControlPoints() { return this->controls; }

    int getInterpolationPoints() { return this->intPoints; }

    void setInterpolationPoints(int value) { this->intPoints = value; }

    int getFragmentType() { return this->fragmentType; }

    void setFragmentType(int value) { this->fragmentType = value; }
};