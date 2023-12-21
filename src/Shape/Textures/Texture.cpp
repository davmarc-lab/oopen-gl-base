#include "Texture.hpp"
#include <vector>

#define DEFAULT_MODE GL_REPEAT

// texture header file
#define STB_IMAGE_IMPLEMENTATION
#include "../../include/texture/stb_image.hpp"

Texture::Texture(const char *path, vector<vec2> texCoord)
{
    this->texCoord = texCoord;
    this->data = stbi_load(path, &this->width, &this->height, &this->channelsNumber, 0);   
}

void Texture::createTexture()
{
    this->createTexture(DEFAULT_MODE);
}

void Texture::createTexture(GLuint mode)
{
    this->textureMode = mode;
    glGenTextures(0, &this->id);
    glBindTexture(GL_TEXTURE_1D, this->id);

    // textures parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (this->data != NULL)
    {
        glTexImage2D(GL_TEXTURE_2D,
                0,
                GL_RGB,
                this->width,
                this->height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                this->data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "---Failed to load texture---" << endl;
    }
    stbi_image_free(this->data);
}