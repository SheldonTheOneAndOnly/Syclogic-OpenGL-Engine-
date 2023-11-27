#version 460 core
#extension GL_ARB_bindless_texture: require

out vec4 fCol;

in vec3 vNor;
in vec3 vCol;
in vec2 vUV;
in vec3 curPos;
in vec3 lightPos;
in vec3 camPos;

layout(bindless_sampler) uniform sampler2D diff0;
layout(bindless_sampler) uniform sampler2D spec0;
layout(bindless_sampler) uniform sampler2D norm0;

uniform vec4 lightCol;

uniform float ambience;
uniform float specular;
uniform float height;

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
    vec2 UV = vUV;

    // Ambience
    vec4 ambient = ambience * lightCol;
    vec4 ambientResult = ambient * textureD;

    // Lighting
    vec3 normal = normalize(vNor);

    if (normalMappingToggle){
        normal = normalize(textureN * 2.0f - 1.0f);
    }

    vec3 lightDir = normalize(lightPos - curPos);

    float dist = length(lightPos - curPos);
    float lightResult = 1.0 / (3.0f * dist * dist + 0.7f + 1.0f);

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0f);
    vec4 diffuseResult = diff * lightCol;

    // Specular
    vec3 halfDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(normal, halfDir), 0.0f), 8);
    if (!specularMappingToggle) textureS = vec3(1.0f, 1.0f, 1.0f);
    float specularResult =  spec * specular * textureS.r;

    // Others
    vec4 mainCol = vec4(vCol.x, vCol.y, vCol.z, 1.0f);

    fCol = ((textureD * (ambientResult + diffuseResult)) * mainCol * lightResult) + (specularResult * lightResult) * lightCol;
}