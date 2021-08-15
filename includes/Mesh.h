#pragma once

#include <string>
#include <vector>

#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"

#include "../includes/Shader.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

struct Material {
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
};

class Mesh {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, 
             const std::vector<Texture>& textures, Material material, float shininess, bool meshUsesTextures);
        void Draw(Shader &shader);
    private:

        // Make default constructor private
        Mesh();

        // render data
        unsigned int VAO, VBO, EBO;

        // mesh data
        std::vector<Vertex>       vertices;
        std::vector<Texture>      textures;
        std::vector<unsigned int> indices;

        // Color
        Material material;

        // Shininess 
        float shininess;

        // Texture Flag
        bool meshUsesTextures;
        
        void setupMesh();
};  