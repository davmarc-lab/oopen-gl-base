#include "Game.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <thread>

#include "../Lib.hpp"
#include "../Color/Color.hpp"
#include "../Window/Window.hpp"
#include "../Shape/ComplexShape2D.hpp"
#include "../Shape/Shape.hpp"
#include "../Shape/Square.hpp"
#include "../Shape/Curve.hpp"
#include "../Scene/Scene.hpp"
#include "../Utils/utils.hpp"



Game::Game(unsigned int width, unsigned int height)
{
    this->state = GAME_NONE;
    this->width = width;
    this->height = height;
#define WIDTH width
#define HEIGHT height
#define ROADLIMIT height - 300

}

mat4 projection = ortho(0.0f, (float)1600, 0.0f, (float)900);

Scene scene = Scene(projection);

void Game::init()
{

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

