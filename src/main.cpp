#include "Lib.hpp"
#include "Window/Window.hpp"
#include "Shape/Shape.hpp"
#include "Shader/Shader.hpp"
#include "Scene/Scene.hpp"

#include <iostream>

#define PI 3.14159265358979323846

const int WIDTH = 800, HEIGHT = 800;

void buildCircle(float cx, float cy, float rx, float ry, Shape2D *shape)
{
    int i;
    float stepA = (2 * PI) / shape->getTriangleNum();
    float t, xx, yy;

    shape->addElementVertex(vec3(cx, cy, 0.0));
    shape->addElementColors(vec4(150.0 / 255.0, 75.0 / 255.0, 0.0, 0.2));

    for (i = 0; i <= shape->getTriangleNum(); i++)
    {
        t = (float)i * stepA;
        xx = cx + rx * cos(t);
        yy = cy + ry * sin(t);
        shape->addElementVertex(vec3(xx, yy, 0.0));
        // Colore
        shape->addElementColors(vec4(0.0, 1.0, 0.0, 1.0));
    }
    shape->setVertexNum(shape->getVertexArray().size());
}

void buildCircleRed(float cx, float cy, float rx, float ry, Shape2D *shape)
{
    int i;
    float stepA = (2 * PI) / shape->getTriangleNum();
    float t, xx, yy;

    shape->addElementVertex(vec3(cx, cy, 0.0));
    shape->addElementColors(vec4(1.0, 0.0, 0.0, 1.0));

    for (i = 0; i <= shape->getTriangleNum(); i++)
    {
        t = (float)i * stepA;
        xx = cx + rx * cos(t);
        yy = cy + ry * sin(t);
        shape->addElementVertex(vec3(xx, yy, 0.0));
        // Colore
        shape->addElementColors(vec4(1.0, 0.0, 0.0, 1.0));
    }
    shape->setVertexNum(shape->getVertexArray().size());
}

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

        Shape2D shape = Shape2D(50);
        buildCircle(0.0, 0.0, 0.3, 0.3, &shape);
        shape.createVertexArray();

        Shape2D shape2 = Shape2D(10);
        buildCircleRed(0.5, -0.5, 0.3, 0.3, &shape2);
        shape2.createVertexArray();

        Scene scene = Scene();

        scene.addShape2dToScene(shape, GL_TRIANGLE_FAN);
        scene.addShape2dToScene(shape2, GL_TRIANGLE_FAN);

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
