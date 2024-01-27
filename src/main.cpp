#include "Game/Game.hpp"
#include "Lib.hpp"
#include "Shape/Shape3D.hpp"
#include "Window/Window.hpp"

#include <iostream>

#define PI 3.14159265358979323846
#define GAME_NAME "Welcome 3D"

const int WIDTH = 1812, HEIGHT = 1017;

int main() {
    Game game = Game(WIDTH, HEIGHT);
    Window window = Window(GAME_NAME, WIDTH, HEIGHT);

    // Initialize all game object and window
    game.init(&window);

    // time variables
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // Start of window loop
    while (!glfwWindowShouldClose(window.getWindow())) {
        // manage frames time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        window.processCloseInput();
        game.processInput(deltaTime, window);

        // update game state
        game.update(deltaTime);

        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        game.render();

        // swap buffers and poll IO events
        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }
    game.clear();
    window.terminateWindow();
    return 0;
}
