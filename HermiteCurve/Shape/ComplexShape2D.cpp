#include "ComplexShape2D.hpp"

ComplexShape2D::ComplexShape2D(int ntriangle, vector<vec3> vertex,
                               vector<vec4> colors, GLuint ebo, mat4 model,
                               vector<vec3> controls, int intPoints, int fragmentType)
    : Shape2D(50, vertex, colors, model)
{
    this->ebo_indexes = ebo;
    this->controls = controls;
    this->intPoints = intPoints;
    this->fragmentType = fragmentType;
}