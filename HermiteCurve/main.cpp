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

void buildBase(ComplexShape2D *shape)
{
    int i = 0;
    shape->addElementVertex(vec3(-1.0, -1.0, 0.0));
    shape->addElementVertex(vec3(1.0, -1.0, 0.0));
    shape->addElementVertex(vec3(-1.0, 1.0, 0.0));
    shape->addElementVertex(vec3(1.0, 1.0, 0.0));

    for (int i = 0; i < shape->getVertexArray().size(); i++)
    {
        shape->addElementColors(vec4(0.13, 0.44, 0.7, 1.0));
    }
    shape->setVertexNum(shape->getVertexArray().size());
    shape->setFragmentType(1);
}

int main()
{
    Window w = Window("Hello triangle", WIDTH, HEIGHT);

    if (w.initializeWindow() == 0)
    {
        Shader shader("resources/vertexShader.vs", "resources/fragmentShader.fs");

        Scene scene = Scene();

        ComplexShape2D sh = ComplexShape2D(50);

        float vertices[] = {
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f};

        vector<vec3> tmp;

        for (int i = 0; i < 3; i++)
        {
            int index = i * 3;
            tmp.push_back(vec3(vertices[index], vertices[index + 1], vertices[index + 2]));
        }

        sh.setVertexArray(tmp);
        sh.setVertexNum(sh.getVertexArray().size());
        scene.addShape2dToScene(sh, GL_TRIANGLES);
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
