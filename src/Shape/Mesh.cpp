#include "Mesh.hpp"
#include <cstddef>

Mesh::Mesh(vector<Vertex> vertex, vector<unsigned int> index, vector<Texture> texture)
{
    this->vertex = vertex;
    this->index = index;
    this->texture = texture;

    this->createVertexArray();
}

void Mesh::createVertexArray()
{
    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
    glGenBuffers(1, &this->ebo);

    glBindVertexArray(this->vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, this->vertex.size() * sizeof(Vertex), &this->vertex[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->index.size() * sizeof(unsigned int), &this->index[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

void Mesh::draw(Shader shader)
{
    GLuint ndiffuse = 1;
    GLuint nspecular = 1;
    
    for (int i = 0; i < this->texture.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);       // activate the proper texture unit

        string number, name = this->texture[i].type;
        number = std::to_string(name == "texture_diffuse" ? ndiffuse++ : nspecular++);

        shader.setInt(("material." + name + number), i);
        glBindTexture(GL_TEXTURE_2D, this->texture[i].id);
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(this->vao);
    glDrawElements(GL_TRIANGLES, this->index.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
