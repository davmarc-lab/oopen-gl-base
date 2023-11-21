#include "Cube.hpp"

void Cube::buildCube()
{
    // front
    this->vertex.push_back(vec3(-1.0, -1.0, 1.0));
    this->colors.push_back(vec4(1.0, 0.0, 0.0, 0.5));
    this->vertex.push_back(vec3(1.0, -1.0, 1.0));
    this->colors.push_back(vec4(0.0, 1.0, 0.0, 0.5));
    this->vertex.push_back(vec3(1.0, 1.0, 1.0));
    this->colors.push_back(vec4(0.0, 0.0, 1.0, 0.5));
    this->vertex.push_back(vec3(-1.0, 1.0, 1.0));
    this->colors.push_back(vec4(1.0, 0.0, 1.0, 0.5));
    // back
    this->vertex.push_back(vec3(-1.0, -1.0, -1.0));
    this->colors.push_back(vec4(1.0, 1.0, 1.0,0.5));
    this->vertex.push_back(vec3(1.0, -1.0, -1.0));
    this->colors.push_back(vec4(1.0, 1.0, 1.0, 0.5));
    this->vertex.push_back(vec3(1.0, 1.0, -1.0));
    this->colors.push_back(vec4(1.0, 1.0, 1.0, 0.5));
    this->vertex.push_back(vec3(-1.0, 1.0, -1.0));
    this->colors.push_back(vec4(1.0, 1.0, 1.0,0.5));

    this->indices.push_back(0); this->indices.push_back(1); this->indices.push_back(2);
    this->indices.push_back(2); this->indices.push_back(3); this->indices.push_back(0);
    this->indices.push_back(1); this->indices.push_back(5); this->indices.push_back(6);
    this->indices.push_back(6); this->indices.push_back(2); this->indices.push_back(1);
    this->indices.push_back(7); this->indices.push_back(6); this->indices.push_back(5);
    this->indices.push_back(5); this->indices.push_back(4); this->indices.push_back(7);
    this->indices.push_back(4); this->indices.push_back(0); this->indices.push_back(3);
    this->indices.push_back(3); this->indices.push_back(7); this->indices.push_back(4);
    this->indices.push_back(4); this->indices.push_back(5); this->indices.push_back(1);
    this->indices.push_back(1); this->indices.push_back(0); this->indices.push_back(4);
    this->indices.push_back(3); this->indices.push_back(2); this->indices.push_back(6);
    this->indices.push_back(6); this->indices.push_back(7); this->indices.push_back(3);
}

Cube::Cube(Color color)
{
    buildCube();
    this->vertex.push_back(vec3(0.0, 0.0, 0.0));
    this->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
    
    this->setVertexNum(this->vertex.size());
    this->indices.push_back(this->getVertexNum() - 1);
    
}
