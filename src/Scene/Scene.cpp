#include "Scene.hpp"

#include <iostream>

Scene::Scene()
{
}

vector<Shape2D> Scene::getSceneShapes2d()
{
    vector<Shape2D> vecs;
    for (int i = 0; i < this->shapes2D.size(); i++)
    {
        vecs.push_back(this->shapes2D[i].first);
    }
    return vecs;
}

void Scene::drawScene()
{
    for (int i = 0; i < this->getSceneElements().size(); i++)
    {
        Shape2D shape = this->getSceneElements()[i].first;
        GLenum renderMode = this->getSceneElements()[i].second;
        glBindVertexArray(shape.getVertexArrayObject());
        glDrawArrays(renderMode, 0, shape.getVertexNum());
    }
}