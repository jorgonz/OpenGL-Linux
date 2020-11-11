#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPosition;

//Light Source
uniform vec3 vc3LightColor;
uniform vec3 vc3LightPosition;

//Object
uniform vec3 vc3ObjColor;

//Camera
uniform vec3 vc3CameraPosition;

void main()
{
    //Ambient
    float fAmbientStrenght = 0.2f;
    vec3 vc3AmbientLight = vc3LightColor * fAmbientStrenght;

    //Diffuse
    vec3 normalizedNormal = normalize(Normal);
    vec3 vc3LightDirection = normalize(vc3LightPosition - FragPosition);
    float fDiffuseStrength = max(dot(normalizedNormal, vc3LightDirection), 0.0f);
    vec3 vc3DiffuseLight = vc3LightColor * fDiffuseStrength;

    //Specular
    float fSpecularStrength = 0.5;
    vec3 vc3FragToCam = normalize(vc3CameraPosition - FragPosition);
    vec3 reflectDir = reflect(-vc3LightDirection, normalizedNormal);
    fSpecularStrength = pow(max(dot(reflectDir, vc3FragToCam), 0.0f) , 64) * fSpecularStrength;
    vec3 vc3SpecularLight = vc3LightColor * fSpecularStrength;

    vec3 vc3LightResult = vc3AmbientLight + vc3DiffuseLight + vc3SpecularLight;

    FragColor = vec4(vc3ObjColor * vc3LightResult, 1.0f);
}