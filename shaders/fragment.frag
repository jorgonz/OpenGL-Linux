#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

//uniform sampler2D ourTexture;

uniform vec3 vc3LightColor;
uniform vec3 vc3ObjColor; 

void main()
{
    //FragColor = texture(ourTexture, TexCoord);
    FragColor = vec4(vc3LightColor * vc3ObjColor, 1.0f);
}