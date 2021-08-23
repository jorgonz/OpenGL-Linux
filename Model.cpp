#include "includes/Model.h"
#include "includes/stb_image.h"
#include "includes/LoadingBar.h"

Model::Model(const std::string& path)
{
    this->loadModel(path);
}

void Model::Draw(Shader &shader)
{
    for(unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw(shader);
    }    
}

void Model::loadModel(const std::string& path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate /*| aiProcess_FlipUVs*/);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    this->directory = path.substr(0, path.find_last_of('/'));

    LoadingBar bar(path, scene->mNumMeshes);
    this->subject.AddObserver(&bar);
    
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));			
    }

    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    /* FILL VERTEX DATA */
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertexToAdd;
        glm::vec3 tempVector;

        // Store vertex position
        tempVector.x = mesh->mVertices[i].x;
        tempVector.y = mesh->mVertices[i].y;
        tempVector.z = mesh->mVertices[i].z;

        // Copy vertex data to struct
        vertexToAdd.position = tempVector;

        // Store Normals
        tempVector.x = mesh->mNormals[i].x;
        tempVector.y = mesh->mNormals[i].y;
        tempVector.z = mesh->mNormals[i].z;

        // Copy normals to struct
        vertexToAdd.normal = tempVector;

        // Copy Texture coordinates if any
        if(mesh->mTextureCoords[0])
        {
            // Store texture coordinates
            glm::vec2 tempVector;
            tempVector.x = mesh->mTextureCoords[0][i].x;
            tempVector.y = mesh->mTextureCoords[0][i].y;
            
            // Copy to struct
            vertexToAdd.texture = tempVector;
        }
        else
        {
            vertexToAdd.texture = glm::vec2(0.0f, 0.0f);
        }
        
        // Vertex Struct is full, add it to the list
        vertices.push_back(vertexToAdd);
    }

    /* FILL VERTEX DATA */
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    /* FILL MATERIAL DATA */
    float shininess;
    Material mat;
    bool meshUsesTextures = false;
    if(mesh->mMaterialIndex >= 0)
    {
        //Load Diffuse and Specular maps
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, 
                                            aiTextureType_DIFFUSE, "diffuseMap");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = loadMaterialTextures(material, 
                                            aiTextureType_SPECULAR, "specularMap");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        // Get the shininess for this specific material
        if(aiReturn_SUCCESS != aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess))
        {
            // if unsuccessful set a default
            shininess = 32.0f;
        }
        
        // Material color
        aiColor3D color;
        if(aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, color))
        {
            mat.ambientColor = glm::vec3(color.r, color.g, color.b);
        }
        else
        {
            mat.ambientColor = glm::vec3(1.0f, 0.5f, 0.31f);
        }

        if(aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, color))
        {
            mat.diffuseColor = glm::vec3(color.r, color.g, color.b);
        }
        else
        {
            mat.diffuseColor = glm::vec3(1.0f, 0.5f, 0.31f);
        }

        if(aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, color))
        {
            mat.specularColor = glm::vec3(color.r, color.g, color.b);
        }
        else
        {
            mat.specularColor = glm::vec3(0.5f, 0.5f, 0.5f);
        }

        if(material->GetTextureCount(aiTextureType_DIFFUSE) + material->GetTextureCount(aiTextureType_SPECULAR) > 0)
        {   
            meshUsesTextures = true;
        }
    }

    //Notify observers, in this case the loading bar
    this->subject.Notify();

    return Mesh(vertices, indices, textures, mat, shininess, meshUsesTextures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        if(!isTextureCached(str))
        {
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            cachedTextures.push_back(texture);
        }        
    }
    return textures;
}

unsigned int Model::TextureFromFile(const char *path, const std::string &directory)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    //stbi_set_flip_vertically_on_load(true);  
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

bool Model::isTextureCached(aiString texture)
{
    //For small n (n < 10) linear search with vector is fast
    for(unsigned int i = 0; i < cachedTextures.size(); i++)
    {
        if(std::strcmp(cachedTextures[i].path.data(), texture.C_Str()) == 0)
        {
            return true;
        }
    }

    return false;
}

