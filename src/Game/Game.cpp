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
Mesh* cube = new Cube(color::BLACK);

void Game::init()
{
    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    scene = Scene(projection);

    Shader shader = Shader("./resources/vertexShader.glsl", "./resources/fragmentShader.glsl");

    shader.use();

    cube->createVertexArray();
    cube->transformMesh(vec3(0), vec3(0.5f), vec3(0, 0, 0), 0);
    /* cube->transformMesh(vec3(0), vec3(1), vec3(0, 1, 0), 45); */

    scene.addShape2dToScene(cube, shader);

    mat4 view = mat4(1.0f);
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    /* view = glm::rotate(view, radians(45.0f), vec3(1, 1, 0)); */

    auto viewLoc = glGetUniformLocation(shader.getId(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

    this->state = GAME_ACTIVE;
}

void Game::processInput(float deltaTime, Window window)
{

}

static float rotval = 0;

void Game::update(float deltaTime)
{
    cube->transformMesh(vec3(0), vec3(1), vec3(0, 1, 0), 1);
    cube->transformMesh(vec3(0), vec3(1), vec3(0, 0, 1), 1);
}

void Game::render()
{
    scene.drawScene();
}

void Game::clear()
{
    scene.clear();
}

