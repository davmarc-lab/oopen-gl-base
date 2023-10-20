#pragma once

#include "../include/glad/glad.h"

#include <iostream>

using namespace std;

class Shader{
    private:
        GLuint id;

        void checkCompileErrors(GLuint shader, string type)
        {
            int success;
            char infoLog[1024];

            if (type != "PROGRAM")
            {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << endl << infoLog << "-- -------------------------------------------------- --" << endl;
                }
            }
            else
            {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                    cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << endl << infoLog << "-- --------------------------------------------------- --" << endl;
                }
            }
        }

    public:

        Shader(const char* vertexPath, const char* fragmentPath);

        void use();

        void setBool(const string &name, bool value);

        void setInt(const string &name, bool value);

        void setFloat(const string &name, bool value);

        GLuint getId() { return this->id; }

        void setId(GLuint val) { this->id = val; }
};
