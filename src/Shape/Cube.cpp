#include "Cube.hpp"

void Cube::buildCube()
{
    // front
    this->vertex.push_back(vec3(-1.0, -1.0, 1.0));
    this->colors.push_back(vec4(1.0, 0.0, 0.0, 0.5));
    this->vertex.push_back(vec3(1.0, -1.0, 1.0));
    this->colors.push_back(vec4(0.0, 1.0, 0.0, 0.5));
    this->vertex.push_back(vec3(1.0, 1.0, 1.0));
    this->colors.push_back(vec4(0.0, 0.0, 1.0, 0.5));
    this->vertex.push_back(vec3(-1.0, 1.0, 1.0));
    this->colors.push_back(vec4(1.0, 0.0, 1.0, 0.5));
    // back
    this->vertex.push_back(vec3(-1.0, -1.0, -1.0));
    this->colors.push_back(vec4(1.0, 1.0, 1.0,0.5));
    this->vertex.push_back(vec3(1.0, -1.0, -1.0));
    this->colors.push_back(vec4(1.0, 1.0, 1.0, 0.5));
    this->vertex.push_back(vec3(1.0, 1.0, -1.0));
    this->colors.push_back(vec4(1.0, 1.0, 1.0, 0.5));
    this->vertex.push_back(vec3(-1.0, 1.0, -1.0));
    this->colors.push_back(vec4(1.0, 1.0, 1.0,0.5));

    this->indices.push_back(0); this->indices.push_back(1); this->indices.push_back(2);
    this->indices.push_back(2); this->indices.push_back(3); this->indices.push_back(0);
    this->indices.push_back(1); this->indices.push_back(5); this->indices.push_back(6);
    this->indices.push_back(6); this->indices.push_back(2); this->indices.push_back(1);
    this->indices.push_back(7); this->indices.push_back(6); this->indices.push_back(5);
    this->indices.push_back(5); this->indices.push_back(4); this->indices.push_back(7);
    this->indices.push_back(4); this->indices.push_back(0); this->indices.push_back(3);
    this->indices.push_back(3); this->indices.push_back(7); this->indices.push_back(4);
    this->indices.push_back(4); this->indices.push_back(5); this->indices.push_back(1);
    this->indices.push_back(1); this->indices.push_back(0); this->indices.push_back(4);
    this->indices.push_back(3); this->indices.push_back(2); this->indices.push_back(6);
    this->indices.push_back(6); this->indices.push_back(7); this->indices.push_back(3);
}

Cube::Cube(Color color)
{
    buildCube();
    this->vertex.push_back(vec3(0.0, 0.0, 0.0));
    this->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));

    this->setVertexNum(this->vertex.size());
    this->indices.push_back(this->getVertexNum() - 1);
}

void Cube::createVertexArray()
{
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    // vbo geometry
    glGenBuffers(1, &this->vbo_g);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_g);
    glBufferData(GL_ARRAY_BUFFER, this->vertex.size() * sizeof(vec3), this->vertex.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // ebo indices
    glGenBuffers(1, &this->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_STATIC_DRAW); 

    // vbo colors
    glGenBuffers(1, &this->vbo_c);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_c);
    glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(vec4), this->colors.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
}

void Cube::draw(Shader shader)
{
    auto matLoc = glGetUniformLocation(shader.getId(), "projection");

        glPointSize(10.0);
    glUniformMatrix4fv(matLoc, 1, GL_FALSE, value_ptr(this->model));

    glBindVertexArray(this->vao);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, (this->indices.size() - 1) * sizeof(GLuint), GL_UNSIGNED_INT, 0);

}

void Cube::clearShape()
{
    cout << "TODO" << endl;
}

