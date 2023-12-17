#include "Game/Game.hpp"
#include "Lib.hpp"
#include "Shape/Mesh.hpp"
#include "Window/Window.hpp"

#include <iostream>

#define PI 3.14159265358979323846

const int WIDTH = 1000, HEIGHT = 900;

int main()
{

    Game game = Game(WIDTH, HEIGHT);
    Window window = Window("Mario Kart", WIDTH, HEIGHT);

    // Initialize all game object and window
    game.init();

    // time variables
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // Start of window loop
    while (!glfwWindowShouldClose(window.getWindow()))
    {
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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
  
        game.render();

        // swap buffers and poll IO events
        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }
    game.clear();
    window.terminateWindow();
    return 0;
}
