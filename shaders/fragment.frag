#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPosition;
in vec2 TextureCoord;

// Structs
struct Material 
{
    sampler2D diffuseMap0;
    sampler2D specularMap0;
    float shininess;
};

struct PointLight 
{
    vec3 position;

    vec3 ambientStrength;
    vec3 diffuseStrength; //this is usually set to the color of the light
    vec3 specularStrength;

    float constantDecay;
    float linearDecay;
    float quadraticDecay;
};

struct DirectionalLight
{
    vec3 direction;

    vec3 ambientStrength;
    vec3 diffuseStrength; //this is usually the set to the color of the light
    vec3 specularStrength;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    vec3 ambientStrength;
    vec3 diffuseStrength; //this is usually set to the color of the light
    vec3 specularStrength;

    float constantDecay;
    float linearDecay;
    float quadraticDecay;

    float innerCutOffAngle;
    float outerCutOffAngle;
};

// Object's material 
uniform Material objectMaterial;

// Camera
uniform vec3 vc3CameraPosition;

// Directional Lights
const int MAX_SIZE_DIRECTIONAL_LIGHTS = 100;
uniform int directionalLightsSize; 
uniform DirectionalLight directionalLights [MAX_SIZE_DIRECTIONAL_LIGHTS];

// Point Lights
const int MAX_SIZE_POINT_LIGHTS = 100;
uniform int pointLightsSize;
uniform PointLight pointLights [MAX_SIZE_POINT_LIGHTS];

// Spot Lights
const int MAX_SIZE_SPOT_LIGHTS = 100;
uniform int spotLightsSize;
uniform SpotLight spotLights [MAX_SIZE_SPOT_LIGHTS];

vec3 CalcDirLight(DirectionalLight lightSource, vec3 fragNormal, vec3 fragToCam)
{
    // Get light direction as a vector from the frag towards the light, aka. invert it
    vec3 vc3LightDirection = normalize(-lightSource.direction);

    // Ambient
    vec3 vc3AmbientLight = lightSource.ambientStrength * vec3(texture(objectMaterial.diffuseMap0, TextureCoord));

    // Diffuse
    vec3 normalizedNormal = normalize(fragNormal);
    float fDiffuseStrength = max(dot(normalizedNormal, vc3LightDirection), 0.0f);
    vec3 vc3DiffuseLight = lightSource.diffuseStrength * (fDiffuseStrength * vec3(texture(objectMaterial.diffuseMap0, TextureCoord)));

    // Specular
    vec3 reflectDir = reflect(-vc3LightDirection, normalizedNormal);
    float fSpecularStrength = pow(max(dot(reflectDir, fragToCam), 0.0f) , objectMaterial.shininess);
    vec3 vc3SpecularLight = lightSource.specularStrength * (fSpecularStrength * vec3(texture(objectMaterial.specularMap0, TextureCoord)));
    
    return vc3AmbientLight + vc3DiffuseLight + vc3SpecularLight;
}

vec3 CalcPointLight(PointLight lightSource, vec3 fragNormal, vec3 fragToCam)
{
    // Get light direction as a vector from the frag towards the light, aka. invert it
    vec3 vc3LightDirection = normalize(lightSource.position - FragPosition);
    float distanceToLight  = length(FragPosition - lightSource.position);

    // Calculate decay based on distance
    float attenuation = 1.0 / (lightSource.constantDecay + lightSource.linearDecay * distanceToLight + 
    lightSource.quadraticDecay * (distanceToLight * distanceToLight));

    // Ambient
    vec3 vc3AmbientLight = lightSource.ambientStrength * vec3(texture(objectMaterial.diffuseMap0, TextureCoord));
    vc3AmbientLight *= attenuation;

    // Diffuse
    vec3 normalizedNormal = normalize(fragNormal);
    float fDiffuseStrength = max(dot(normalizedNormal, vc3LightDirection), 0.0f);
    vec3 vc3DiffuseLight = lightSource.diffuseStrength * (fDiffuseStrength * vec3(texture(objectMaterial.diffuseMap0, TextureCoord)));
    vc3DiffuseLight *= attenuation;

    // Specular
    vec3 reflectDir = reflect(-vc3LightDirection, normalizedNormal);
    float fSpecularStrength = pow(max(dot(reflectDir, fragToCam), 0.0f) , objectMaterial.shininess);
    vec3 vc3SpecularLight = lightSource.specularStrength * (fSpecularStrength * vec3(texture(objectMaterial.specularMap0, TextureCoord)));
    vc3SpecularLight *= attenuation;
    
    return vc3AmbientLight + vc3DiffuseLight + vc3SpecularLight;
}

vec3 CalcSpotLight(SpotLight lightSource, vec3 fragNormal, vec3 fragToCam)
{
    // Get light direction as a vector from the frag towards the light, aka. invert it
    vec3 vc3LightDirection = normalize(lightSource.position - FragPosition);
    float distanceToLight  = length(FragPosition - lightSource.position);

    // Calculate decay based on distance
    float attenuation = 1.0 / (lightSource.constantDecay + lightSource.linearDecay * distanceToLight + 
    lightSource.quadraticDecay * (distanceToLight * distanceToLight));

    float theta = dot(vc3LightDirection, normalize(-lightSource.direction));
    float epsilon = (lightSource.innerCutOffAngle - lightSource.outerCutOffAngle);
    float intensity = clamp((theta - lightSource.outerCutOffAngle) / epsilon, 0.0, 1.0);

    // Ambient
    vec3 vc3AmbientLight = lightSource.ambientStrength * vec3(texture(objectMaterial.diffuseMap0, TextureCoord));
    vc3AmbientLight *= attenuation;

    // Diffuse
    vec3 normalizedNormal = normalize(fragNormal);
    float fDiffuseStrength = max(dot(normalizedNormal, vc3LightDirection), 0.0f);
    vec3 vc3DiffuseLight = lightSource.diffuseStrength * (fDiffuseStrength * vec3(texture(objectMaterial.diffuseMap0, TextureCoord)));
    vc3DiffuseLight *= intensity;
    vc3DiffuseLight *= attenuation;

    // Specular
    vec3 reflectDir = reflect(-vc3LightDirection, normalizedNormal);
    float fSpecularStrength = pow(max(dot(reflectDir, fragToCam), 0.0f) , objectMaterial.shininess);
    vec3 vc3SpecularLight = lightSource.specularStrength * (fSpecularStrength * vec3(texture(objectMaterial.specularMap0, TextureCoord)));
    vc3SpecularLight *= intensity;
    vc3SpecularLight *= attenuation;

    return vc3AmbientLight + vc3DiffuseLight + vc3SpecularLight;   
}

void main()
{
    vec3 vc3LightResult = vec3(0.0f);
    vec3 vc3FragToCam = normalize(vc3CameraPosition - FragPosition);

    // Directional Lights
    for(int i = 0; i < directionalLightsSize; i++)
    {
        vc3LightResult += CalcDirLight(directionalLights[i], Normal, vc3FragToCam);
    }

    // Point Lights
    for(int i = 0; i < pointLightsSize; i++)
    {
        vc3LightResult += CalcPointLight(pointLights[i], Normal, vc3FragToCam);
    }

    // Spot Lights
    for(int i = 0; i < spotLightsSize; i++)
    {
        vc3LightResult += CalcSpotLight(spotLights[i], Normal, vc3FragToCam);
    }

    FragColor = vec4(vc3LightResult, 1.0f);
}