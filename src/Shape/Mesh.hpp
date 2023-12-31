#pragma once

#include "../Lib.hpp"
#include "../Shader/Shader.hpp"

#include <vector>

struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 texCoords;
    vec3 tangent;
    vec3 biTangent;
};

struct Texture {
    GLuint id;
    string type;
    string path;
};

class Mesh
{
    private:
        GLuint vao;
        GLuint vbo;
        GLuint ebo;
        vector<Vertex> vertex;
        vector<unsigned int> index;
        vector<Texture> texture;

        void createVertexArray();
    public:
        Mesh() {}

        Mesh(vector<Vertex> vertex, vector<unsigned int> index, vector<Texture> texture);

        void draw(Shader shader);
};
