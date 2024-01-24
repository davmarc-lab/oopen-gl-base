#include "Game.hpp"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/dual_quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

#include "../Lib.hpp"
#include "../Color/Color.hpp"
#include "../Camera/Camera.hpp"
#include "../Window/Window.hpp"
#include "../Shape/Shape3D.hpp"
#include "../Shape/Cube.hpp"
#include "../Scene/Scene.hpp"
#include "../Shape/Model.hpp"
#include "../Light/SpotLight.hpp"
#include "../Chunk/Chunk.hpp"

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
Shape3D* cube = new Cube(color::BLUE);
Camera camera = Camera();
Shader cubeShader;
Texture texture;

struct Mouse
{
    bool firstMouse = true;
    float lastX;
    float lastY;
} mouse;

void mouseMovementCallback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    
    if (mouse.firstMouse)
    {
        mouse.firstMouse = false;
        mouse.lastX = xpos;
        mouse.lastY = ypos;
    }

    float xoffset = xpos - mouse.lastX;
    float yoffset = ypos - mouse.lastY;

    mouse.lastX = xpos;
    mouse.lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

void Game::init(Window* window)
{
    projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    scene = Scene(projection);

    cubeShader = Shader("./resources/vertexShader.glsl", "./resources/fragmentShader.glsl");
    cubeShader.use();
    cubeShader.setMat4("projection", projection);

    cube->createVertexArray();
    cube->transformMesh(vec3(0), vec3(0.01f), vec3(1), 0);
    texture = Texture("resources/textures/dirt.jpg", cube->getTextureCoords());
    texture.createTexture();
    cube->attachTexture(texture);
    cubeShader.setInt("ourTexture", texture.getId());

    camera.moveCamera(vec3(0, 0, 2));

    scene.addShape2dToScene(cube, cubeShader);

    // sets the mouse callback function
    glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window->getWindow(), mouseMovementCallback);

    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window->getWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    Chunk chunk = Chunk(8);

    this->state = GAME_ACTIVE;
}

void Game::processInput(float deltaTime, Window window)
{
    // camera input
    float cameraVelocity = camera.getCameraVelocity() * deltaTime;
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
        auto pos = camera.getCameraPosition() - cameraVelocity * camera.getCameraRight();
        camera.moveCamera(pos);
    }
    if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        auto pos = camera.getCameraPosition() + cameraVelocity * camera.getCameraRight();
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
    cubeShader.setMat4("view", camera.getViewMatrix());
}

void Game::render()
{
    Chunk chunk = Chunk(8);
    chunk.drawChunk(cubeShader);
    glBindTexture(GL_TEXTURE_2D, texture.getId());
    glActiveTexture(GL_TEXTURE1);
    scene.drawScene();
}

void Game::clear()
{
    scene.clear();
}

