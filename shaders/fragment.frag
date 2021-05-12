#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPosition;

//Structs
struct Material {
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
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

//uniform vec3 vc3LightColor;
//uniform vec3 vc3LightPosition;

//Camera
uniform vec3 vc3CameraPosition;

void main()
{
    //Ambient
    vec3 vc3AmbientLight = lightSource.ambientStrength * objectMaterial.ambientColor;

    //Diffuse
    vec3 normalizedNormal = normalize(Normal);
    vec3 vc3LightDirection = normalize(lightSource.position - FragPosition);
    float fDiffuseStrength = max(dot(normalizedNormal, vc3LightDirection), 0.0f);
    vec3 vc3DiffuseLight = lightSource.diffuseStrength * (fDiffuseStrength * objectMaterial.diffuseColor);

    //Specular
    vec3 vc3FragToCam = normalize(vc3CameraPosition - FragPosition);
    vec3 reflectDir = reflect(-vc3LightDirection, normalizedNormal);
    float fSpecularStrength = pow(max(dot(reflectDir, vc3FragToCam), 0.0f) , objectMaterial.shininess);
    vec3 vc3SpecularLight = lightSource.specularStrength * (fSpecularStrength * objectMaterial.specularColor);

    vec3 vc3LightResult = vc3AmbientLight + vc3DiffuseLight + vc3SpecularLight;

    FragColor = vec4(vc3LightResult, 1.0f);
}