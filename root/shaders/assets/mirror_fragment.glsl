#version 460 core
#extension GL_ARB_bindless_texture: require

out vec4 fCol;

in vec3 vNor;
in vec3 vRefNor;
in vec2 vUV;

layout(bindless_sampler) uniform sampler2D diff0;

layout(bindless_sampler) uniform samplerCube skybox;

uniform float ambience;
uniform float roughness;

uniform vec3 lightAng;

void main(){
    float b = max(dot(normalize(-lightAng), normalize(vNor)), 0.0f) + ambience;
    fCol = texture(diff0, vUV) * b;

    vec4 refCol = texture(skybox, vRefNor);
    fCol = mix(fCol, refCol, 1.0f - clamp(roughness, 0.0f, 1.0f));
}