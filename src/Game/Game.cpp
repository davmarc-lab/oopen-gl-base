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
Shader shader, cubeShader;
Texture texture;
Model backPack;

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

    shader = Shader("./resources/modelVertexShader.glsl", "./resources/modelFragmentShader.glsl");
    shader.use();
    shader.setMat4("projection", projection);

    cubeShader = Shader("./resources/vertexShader.glsl", "./resources/fragmentShader.glsl");
    cubeShader.use();
    cubeShader.setMat4("projection", projection);

    // Model load test
    backPack = Model("./resources/models/Try/First.obj", Flip::VERTICALLY);

    cube->createVertexArray();
    cube->transformMesh(vec3(0), vec3(0.3f), vec3(1), 0);

    camera.moveCamera(vec3(0, 0, 4));

    scene.addShape2dToScene(cube, cubeShader);

    // sets the mouse callback function
    glfwSetInputMode(window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window->getWindow(), mouseMovementCallback);

    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(window->getWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

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
    shader.setMat4("view", camera.getViewMatrix());
    shader.setMat4("model", translate(mat4(1.0f), vec3(0)));

    cube->transformMesh(vec3(0), vec3(1), vec3(0, 1, 0), 30 * deltaTime);
}

void Game::render()
{
    scene.drawScene();
    backPack.draw(shader);
}

void Game::clear()
{
    scene.clear();
}

