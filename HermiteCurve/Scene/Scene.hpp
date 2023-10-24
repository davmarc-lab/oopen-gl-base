#pragma once

#include "../Shape/Shape.hpp"

#include <utility>

class Scene
{
private:
    vector<pair<Shape2D, GLenum>> shapes2D;

public:
    Scene();

    void addShape2dToScene(Shape2D shape, GLenum mode) { this->shapes2D.push_back(pair(shape, mode)); }

    vector<pair<Shape2D, GLenum>> getSceneElements() { return this->shapes2D; }

    GLenum getRenderMode(Shape2D shape);

    void drawScene(GLuint id);
};