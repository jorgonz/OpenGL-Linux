#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 mx4Model;
uniform mat4 mx4View;
uniform mat4 mx4Proj;

//out vec2 TexCoord;

void main()
{
    gl_Position = mx4Proj * mx4View * mx4Model * vec4(aPos, 1.0);
    //TexCoord = aTexCoord;
}