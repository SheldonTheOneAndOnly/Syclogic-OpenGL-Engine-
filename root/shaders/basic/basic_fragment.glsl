#version 460 core

out vec4 fCol;

in vec3 vNor;
in vec3 curPos;
in vec3 vCol;
in vec2 vUV;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform vec4 lightCol;
uniform vec3 lightPos;
uniform vec3 camPos;

uniform float ambience;
uniform float specular;

void main(){
	vec3 normal = normalize(vNor);
	vec3 lightDir = normalize(lightPos - curPos);

	float diff = max(dot(vNor, lightDir), 0.0f);

	vec3 viewDir = normalize(camPos - curPos);
	vec3 reflectionDir = reflect(-lightDir, vNor);
	float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 8);
	float spec = specAmount * specular;

	fCol = texture(tex0, vUV) * lightCol * (diff + ambience) + texture(tex1, vUV).r * spec;
}