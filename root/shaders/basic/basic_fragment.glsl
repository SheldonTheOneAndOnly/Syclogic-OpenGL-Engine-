#version 460 core

out vec4 fCol;

in vec3 vNor;
in vec3 vCol;
in vec2 vUV;
in vec3 curPos;
in vec3 lightPos;
in vec3 camPos;

uniform vec4 lightCol;

uniform float ambience;
uniform float specular;
uniform float height;

void main(){
    // Variables
    vec3 viewDir = normalize(camPos - curPos);
    vec4 mainCol = vec4(vCol.x, vCol.y, vCol.z, 1.0f);

    vec4 ambient = ambience * lightCol;
    vec4 ambientResult = ambient * mainCol;

    // Lighting
    vec3 normal = normalize(vNor);

    vec3 lightDir = normalize(lightPos - curPos);

    float dist = length(lightPos - curPos);
    float lightResult = 1.0 / (3.0f * dist * dist + 0.7f + 1.0f);

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0f);
    vec4 diffuseResult = diff * lightCol;

    // Specular
    vec3 halfDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(normal, halfDir), 0.0f), 8);
    float specularResult =  spec * specular;

    fCol = ((ambientResult + diffuseResult) * mainCol * lightResult) + (specularResult * lightResult) * lightCol;
}