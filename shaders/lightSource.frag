#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

//uniform sampler2D ourTexture;

uniform vec3 vc3LightColor;
uniform vec3 vc3ObjColor; 

void main()
{
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}