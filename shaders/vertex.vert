#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoord;

uniform mat4 mx4Model;
uniform mat4 mx4View;
uniform mat4 mx4Proj;

//out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPosition;
out vec2 TextureCoord;

void main()
{
    //Pass texture coordinates to fragment shader
    TextureCoord = aTextureCoord;

    //Calculate the position of the fragent and its normal
    //And pass that to the fragment shader
    FragPosition = vec3(mx4Model * vec4(aPos, 1.0f));   
    Normal = mat3(transpose(inverse(mx4Model))) * aNormal;
    gl_Position = mx4Proj * mx4View * mx4Model * vec4(aPos, 1.0);
}