#include "Game.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <thread>

#include "../Lib.hpp"
#include "../Color/Color.hpp"
#include "../Window/Window.hpp"
#include "../Shape/Mesh.hpp"
#include "../Shape/Cube.hpp"
#include "../Scene/Scene.hpp"

Game::Game(unsigned int width, unsigned int height)
{
    this->state = GAME_NONE;
    this->width = width;
    this->height = height;
#define WIDTH width
#define HEIGHT height
#define ROADLIMIT height - 300

}

mat4 projection;
Scene scene;

void Game::init()
{
    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    scene = Scene(projection);

    Shader shader = Shader("./resources/vertexShader.glsl", "./resources/fragmentShader.glsl");

    Mesh* cube = new Cube(vec4(1, 1, 0, 1));
    cube->createVertexArray();

    cube->setModelMatrix(mat4(1.0f));
    cube->translateShape(vec3(0, 0, 0));
    cube->scaleShape(vec3(500, 500, 500));

    scene.addShape2dToScene(cube, shader);

    this->state = GAME_ACTIVE;

    /* bananaHelper.setYVelocity(0.05f); */
}

void Game::processInput(float deltaTime, Window window)
{

}

void Game::update(float deltaTime)
{

}

void Game::render()
{
    scene.drawScene();
}

void Game::clear()
{
    scene.clear();
}

