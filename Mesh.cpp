#include "includes/Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures, 
           Material material, float shininess, bool meshUsesTextures)
{
    this->vertices  = std::move(vertices);
    this->indices   = std::move(indices);
    this->textures  = std::move(textures);
    this->material  = material;
    this->shininess = shininess;
    this->meshUsesTextures = meshUsesTextures;
    setupMesh();
}

void Mesh::setupMesh()
{
    // Generate a VBO, EBO, and VAO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO
    glBindVertexArray(VAO);
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Fill VBO with vertex data
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    // Fill EBO with indices data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
                 &indices[0], GL_STATIC_DRAW);

     // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));

    // Unbind the VAO
    glBindVertexArray(0);
}

void Mesh::Draw(Shader &shader) 
{
    unsigned int diffuseNr = 0;
    unsigned int specularNr = 0;
    for(unsigned int i = 0; i < this->textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuseMapN)
        std::string number;
        std::string name = this->textures[i].type;
        if(name == "diffuseMap")
            number = std::to_string(diffuseNr++);
        else if(name == "specularMap")
            number = std::to_string(specularNr++);

        shader.setFloat(("objectMaterial." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);
    
    shader.setBool("objectMaterial.useTextureData",   this->meshUsesTextures);
    shader.setVector3("objectMaterial.ambientColor",  this->material.ambientColor);
    shader.setVector3("objectMaterial.diffuseColor",  this->material.diffuseColor);
    shader.setVector3("objectMaterial.specularColor", this->material.specularColor);
    shader.setFloat("objectMaterial.shininess",       this->shininess);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
} 