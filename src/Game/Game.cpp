#include "Game.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <thread>

#include "../Lib.hpp"
#include "../Color/Color.hpp"
#include "../Camera/Camera.hpp"
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

}

mat4 projection;
Scene scene;
Mesh* cube = new Cube(color::BLACK);
Camera camera = Camera();
Shader shader;

void Game::init()
{
    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 500.0f);
    scene = Scene(projection);

    shader = Shader("./resources/vertexShader.glsl", "./resources/fragmentShader.glsl");

    shader.use();

    cube->createVertexArray();
    cube->transformMesh(vec3(0), vec3(1), vec3(1), 0);
    camera.setCameraPosition(vec3(0, 0, 4));

    scene.addShape2dToScene(cube, shader);

    this->state = GAME_ACTIVE;
}

void Game::processInput(float deltaTime, Window window)
{
    // camera input
    // IMPORTANT< CHANGE THIS UGLY METHOD
    float cameraVelocity = 4 * deltaTime;
    if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        auto pos = camera.getCameraPosition() + cameraVelocity * camera.getCameraFront();
        camera.moveCamera(pos);
    }
    if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        auto pos = camera.getCameraPosition() - cameraVelocity * camera.getCameraFront();
        camera.moveCamera(pos);
    }
    if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        auto pos = camera.getCameraPosition();
        pos -= glm::normalize(glm::cross(camera.getCameraFront(), camera.getCameraUp())) * cameraVelocity;
        camera.moveCamera(pos);
    }
    if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        auto pos = camera.getCameraPosition();
        pos += glm::normalize(glm::cross(camera.getCameraFront(), camera.getCameraUp())) * cameraVelocity;
        camera.moveCamera(pos);
    }
    if (glfwGetKey(window.getWindow(), GLFW_KEY_E) == GLFW_PRESS)
    {
        auto pos = camera.getCameraPosition() + cameraVelocity * camera.getCameraUp();
        camera.moveCamera(pos);
    }
    if (glfwGetKey(window.getWindow(), GLFW_KEY_Q) == GLFW_PRESS)
    {
        auto pos = camera.getCameraPosition() - cameraVelocity * camera.getCameraUp();
        camera.moveCamera(pos);
    }
}

static float rotval = 0;

void Game::update(float deltaTime)
{
    /* cube->transformMesh(vec3(0.1, 0, 0), vec3(1), vec3(0, 1, 0), 0); */
    cube->transformMesh(vec3(0.002, 0, 0), vec3(1), vec3(0, 1, 0), 0);

    auto viewLoc = glGetUniformLocation(shader.getId(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(camera.getViewMatrix()));

}

void Game::render()
{
    scene.drawScene();
}

void Game::clear()
{
    scene.clear();
}

