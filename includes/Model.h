#pragma once
#include <vector>

//Assimp
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Mesh.h"
#include "Subject.h"

class Model 
{
    public:
        Model(const std::string& path);
        void Draw(Shader &shader);
        
    private:
        // model data
        std::vector<Mesh> meshes;
        std::string directory;
        std::vector<Texture> cachedTextures;

        void loadModel(const std::string& path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             std::string typeName);
        unsigned int TextureFromFile(const char *path, const std::string &directory);
        bool isTextureCached(aiString texture);

        Subject subject;
};