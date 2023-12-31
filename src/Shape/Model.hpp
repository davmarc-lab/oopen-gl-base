#pragma once

#include "../Lib.hpp"
#include "../include/texture/stb_image.hpp"
#include "Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h>

#include <vector>

class Model
{
    private:
        vector<Texture> textures_loaded;
        vector<Mesh> meshes;
        string directory;
        bool gammaCorrection;

        void loadModel(string path);

        void processNode(aiNode *node, const aiScene *scene);
       
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

    public:
        Model(const char* path, bool gamma = false) : gammaCorrection(gamma)
        {
            loadModel(path);
        }

        void draw(Shader shader);
};
