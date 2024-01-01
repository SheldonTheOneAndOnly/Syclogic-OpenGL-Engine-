#version 460 core
#extension GL_ARB_bindless_texture: require

out vec4 fCol;

in vec3 vNor;
in vec3 vRefNor;
in vec3 vCol;
in vec2 vUV;
in vec3 curPos;
in vec3 lightPos;
in vec3 camPos;

// Textures
layout(bindless_sampler) uniform sampler2D diff0;
layout(bindless_sampler) uniform sampler2D spec0;
layout(bindless_sampler) uniform sampler2D norm0;

layout(bindless_sampler) uniform samplerCube skybox;

// Light
uniform vec4 lightCol;
uniform vec3 lightAng;
uniform int lightType;

uniform float atten_a;
uniform float atten_b;

// Variables
uniform float ambience;
uniform float specular;
uniform float metallic;
uniform float roughness;

const int kernelSize = 9;
float kernel[kernelSize];

uniform mat4 projection, view, model;

// DEBUG
uniform bool normalMappingToggle;
uniform bool specularMappingToggle;

void main(){
    // Load Textures
    vec4 textureD = texture(diff0, vUV);
    vec3 textureS = texture(spec0, vUV).rgb;
    vec3 textureN = texture(norm0, vUV).rgb;

    // Variables
    vec3 viewDir = normalize(camPos - curPos);

    // Ambience
    vec4 ambient = ambience * lightCol;
    vec4 ambientResult = ambient * textureD;

    // Lighting
    vec3 normal = normalize(vNor);

    if (normalMappingToggle) {
        normal = normalize(textureN * 2.0f - 1.0f);
    }

    vec3 lightDir;
    
    float dist = length(lightPos - curPos);
    float lightResult = 1.0 / (atten_a * dist * dist + atten_b + 1.0f);

    if (lightType == 0) {
        // Point light
        lightDir = normalize(lightPos - curPos);
    } else if (lightType == 1) {
        // Directional light
        lightDir = normalize(-lightAng);
    } else if (lightType == 2) {
        // Spot light
        float inner = 0.9f;
        float outer = 0.95f;
        
        lightDir = normalize(lightPos - curPos);
        float angle = dot(lightAng, -lightDir);
        lightResult = clamp((angle - outer) / (inner - outer), 0.0f, 1.0f);
    }

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0f);
    vec4 diffuseResult = diff * lightCol;

    // Specular
    vec3 halfDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(normal, halfDir), 0.0f), 8);
    if (!specularMappingToggle) textureS = vec3(1.0f, 1.0f, 1.0f);
    float specularResult = spec * specular * textureS.r;

    // Roughness
    vec4 refCol = texture(skybox, normalize(vRefNor));
    refCol = refCol + (textureD * (1.0f - metallic));

    // Others
    vec4 mainCol = vec4(vCol.x, vCol.y, vCol.z, 1.0f);

    fCol = ((textureD * (ambientResult + diffuseResult)) * mainCol * lightResult) + (specularResult * lightResult) * lightCol;
    if (lightType == 1) fCol = (textureD * (ambientResult + diffuseResult) * mainCol) + specularResult * lightCol;
}