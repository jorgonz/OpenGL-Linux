#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPosition;
in vec2 TextureCoord;

//Structs
struct Material {
    sampler2D ambientDiffuseMap;
    sampler2D specularMap;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambientStrength;
    vec3 diffuseStrength; //this is usually the set to the color of the light
    vec3 specularStrength;
};

//Light Source
uniform Light lightSource;  

//Object's material 
uniform Material objectMaterial;

//Camera
uniform vec3 vc3CameraPosition;

void main()
{
    //Ambient
    vec3 vc3AmbientLight = lightSource.ambientStrength * vec3(texture(objectMaterial.ambientDiffuseMap, TextureCoord));

    //Diffuse
    vec3 normalizedNormal = normalize(Normal);
    vec3 vc3LightDirection = normalize(lightSource.position - FragPosition);
    float fDiffuseStrength = max(dot(normalizedNormal, vc3LightDirection), 0.0f);
    vec3 vc3DiffuseLight = lightSource.diffuseStrength * (fDiffuseStrength * vec3(texture(objectMaterial.ambientDiffuseMap, TextureCoord)));

    //Specular
    vec3 vc3FragToCam = normalize(vc3CameraPosition - FragPosition);
    vec3 reflectDir = reflect(-vc3LightDirection, normalizedNormal);
    float fSpecularStrength = pow(max(dot(reflectDir, vc3FragToCam), 0.0f) , objectMaterial.shininess);
    vec3 vc3SpecularLight = lightSource.specularStrength * (fSpecularStrength * vec3(texture(objectMaterial.specularMap, TextureCoord)));

    vec3 vc3LightResult = vc3AmbientLight + vc3DiffuseLight + vc3SpecularLight;

    FragColor = vec4(vc3LightResult, 1.0f);
}