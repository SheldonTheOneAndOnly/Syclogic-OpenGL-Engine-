#version 460 core

out vec4 fCol;

in vec3 vNor;
in vec3 vCol;
in vec2 vUV;
in vec3 curPos;
in vec3 lightPos;
in vec3 camPos;

uniform sampler2D diff0;
uniform sampler2D spec0;
uniform sampler2D norm0;
uniform sampler2D disp0;

uniform vec4 lightCol;

uniform float ambience;
uniform float specular;
uniform float height;

// DEBUG
uniform bool normalMappingToggle;
uniform bool parallaxMappingToggle;

void main(){
    // Displacement
    vec4 textureN = texture(norm0, vUV);
    vec3 viewDir = normalize(camPos - curPos);

    vec2 UV = vUV;

    if (parallaxMappingToggle){
        const float minL = 8.0f;
        const float maxL = 64.0f;
        float numL = 10.0f;
        float lDepth = 1.0f / numL;
        float curLDepth = 0.0f;

        vec2 S = viewDir.xy / viewDir.z * height;
        vec2 deltaUVs = S / numL;

        float curDepthMapValue = 1.0f - textureN.a;

        while(curLDepth < curDepthMapValue)
        {
            UV -= deltaUVs;
            curDepthMapValue = 1.0 - textureN.a;
            curLDepth += lDepth;
        }

        vec2 prevUVs = UV + deltaUVs;
        float depthResult = curDepthMapValue - curLDepth;
        float pastDepth = 1.0f - textureN.a - curLDepth + lDepth;
        float weight = depthResult / (depthResult - pastDepth);
        UV = prevUVs * weight + UV * (1.0f - weight);
    }

    // Load Textures
    vec4 textureD = texture(diff0, UV);
    vec3 textureS = texture(spec0, UV).rgb;
    textureN = texture(norm0, UV);

    // Ambience
    vec4 ambient = ambience * lightCol;
    vec4 ambientResult = ambient * textureD;

    // Lighting
    vec3 normal = normalize(vNor);

    if (normalMappingToggle){
        normal = normalize(textureN.rgb * 2.0f - 1.0f);
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
    float specularResult =  spec * specular * textureS.r;

    // Others
    vec4 mainCol = vec4(vCol.x, vCol.y, vCol.z, 1.0f);

    fCol = ((textureD * (ambientResult + diffuseResult)) * mainCol * lightResult) + (specularResult * lightResult) * lightCol;
}