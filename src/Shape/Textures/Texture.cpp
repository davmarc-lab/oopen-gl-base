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
    if (this->data != NULL)
    {
        GLenum format;
        if (this->channelsNumber == 1)
            format = GL_RED;
        else if (this->channelsNumber == 3)
            format = GL_RGB;
        else if (this->channelsNumber == 4)
            format = GL_RGBA;
        this->textureMode = mode;
        glGenTextures(1, &this->id);
        glBindTexture(GL_TEXTURE_1D, this->id);

        glTexImage2D(GL_TEXTURE_2D,
                0,
                format,
                this->width,
                this->height,
                0,
                format,
                GL_UNSIGNED_BYTE,
                this->data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // textures parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        cout << "---Failed to load texture---" << endl;
    }
    stbi_image_free(this->data);
}
