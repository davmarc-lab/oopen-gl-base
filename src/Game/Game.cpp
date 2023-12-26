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
#include "../Light/SpotLight.hpp"

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
Mesh* cube = new Cube(color::BLUE);
Camera camera = Camera();
Shader shader;
Texture texture;

void Game::init()
{
    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 500.0f);
    scene = Scene(projection);

    shader = Shader("./resources/lightVertexShader.glsl", "./resources/lightFragmentShader.glsl");

    shader.use();

    cube->createVertexArray();
    cube->transformMesh(vec3(0), vec3(1), vec3(1), 0);

    texture = Texture("resources/textures/woddenContainer.jpg", cube->getTextureCoords());
    texture.createTexture();
    cube->attachTexture(texture);
    shader.setInt("ourTexture", texture.getId());

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
    if (glfwGetKey(window.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        auto pos = camera.getCameraPosition() + cameraVelocity * camera.getCameraUp();
        camera.moveCamera(pos);
    }
    if (glfwGetKey(window.getWindow(), GLFW_KEY_LEFT_SHIFT)  == GLFW_PRESS)
    {
        auto pos = camera.getCameraPosition() - cameraVelocity * camera.getCameraUp();
        camera.moveCamera(pos);
    }
}

static float rotval = 0;

void Game::update(float deltaTime)
{
    auto viewLoc = glGetUniformLocation(shader.getId(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(camera.getViewMatrix()));
    shader.setVec3("viewPos", camera.getCameraPosition());

    shader.setInt("material.diffuse", texture.getId());

    shader.setFloat("material.shininess", 32.0f);

    cube->transformMesh(vec3(0), vec3(1), vec3(0, 1, 0), 30 * deltaTime);
}

void Game::render()
{
    glBindTexture(GL_TEXTURE_2D, texture.getId());
    shader.setInt("ourTexture", texture.getId());
    SpotLight dl = SpotLight(camera.getCameraPosition(),
            camera.getCameraFront(),
            cos(radians(12.5f)),
            cos(radians(15.5f)));
    dl.setAmbient(vec3(0.1));
    dl.setDiffuse(vec3(0.8));
    dl.setSpecular(vec3(1));
    dl.setConstantValue(1);
    dl.setLinearValue(0.09);
    dl.setQuadraticValue(0.032);
    dl.setSmooth(true);

    dl.drawLight(shader);
    scene.drawScene();
}

void Game::clear()
{
    scene.clear();
}

