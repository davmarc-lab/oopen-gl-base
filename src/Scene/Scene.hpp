#pragma once

#include "../Shape/ComplexShape3D.hpp"
#include "../Shader/Shader.hpp"
#include <algorithm>
#include <cstddef>
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>
#include <utility>

using namespace std;

enum ShapeType
{
    ENEMY,
    TRIAG,
    PLAYER,
    NONE
};

class Element
{
    public:
        ComplexShape3D* shape;
        Shader shader;
        ShapeType type;

        Element(ComplexShape3D* shape, Shader shader, ShapeType type)
        {
            this->shape = shape;
            this->shader = shader;
            this->type = type;
        }
};

/*
 * This class creates a Scene that can be used to display ComplexShape3D object into the window.
 */
class Scene
{
    private:
        // This vector store a ComplexShape3D and the corresponding Shader.
        vector<Element> shapes;
        // It represent the porjection matrix used to draw each element of the Scene.
        mat4 projection;

    public:
        // This constructor creates an empty scene.
        Scene() {}

        // This constructor create a scene with a given projection matrix.
        Scene(mat4 projection);

        // Add to the scene a given shape and his shader.
        void addShape2dToScene(ComplexShape3D* shape, Shader shader) { this->shapes.push_back(Element(shape, shader, NONE)); }

        // Add to the scene a given shape and his shader.
        void addShape2dToScene(ComplexShape3D* shape, Shader shader, ShapeType type) { this->shapes.push_back(Element(shape, shader, type)); }

        // Retrieves all the element of the scene in a vector<pair<ComplexShape3D*, Shader>>.
        vector<Element> getSceneElements() { return this->shapes; }

        // This method reshape the entire scene, should be followed by a modification of the projection.
        void reshape(int width, int height);

        // Set the projection matrix with a given matrix.
        void setProjectionMatrix(mat4 projection) { this->projection = mat4(projection); }

        // This method call all draw(shader) method of each shape implemented from ComplexShape3D class.
        void drawScene();

        void clear();
};
