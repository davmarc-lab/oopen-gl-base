#include "Lib.hpp"
#include "Window/Window.hpp"
#include "Shape/Shape.hpp"
#include "Shape/ComplexShape2D.hpp"
#include "Shader/Shader.hpp"
#include "Scene/Scene.hpp"

#include <iostream>

#define PI 3.14159265358979323846

const int WIDTH = 800, HEIGHT = 800;

void initWindowView(Shader shader)
{
    mat4 view = mat4(1.0f);
    mat4 projection = mat4(1.0f);
    view = translate(view, vec3(0.0f, 0.0f, 0.0f));
    // projection = perspective(radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f);
    projection = ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT);
    GLuint viewLoc = glGetUniformLocation(shader.getId(), "view");
    GLuint projLoc = glGetUniformLocation(shader.getId(), "projection");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));
}

int main()
{
    Window w = Window("Hello triangle", WIDTH, HEIGHT);

    if (w.initializeWindow() == 0)
    {
        Shader shader("resources/vertexShader.vs", "resources/fragmentShader.fs");

        Scene scene = Scene();

        ComplexShape2D sh = ComplexShape2D();

        shader.use();
        initWindowView(shader);

        while (!glfwWindowShouldClose(w.getWindow()))
        {
            // input
            w.processCloseInput();

            // render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            scene.drawScene(shader.getId());

            // swap buffers and poll IO events
            glfwSwapBuffers(w.getWindow());
            glfwPollEvents();
        }
        w.terminateWindow();
    }
    else
    {
        cout << "Cannot start the application, due to GLFW error" << endl;
        return -1;
    }

    return 0;
}
