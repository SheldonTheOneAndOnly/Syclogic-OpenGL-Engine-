#version 460 core

out vec4 fCol;

in vec3 vNor;
in vec3 curPos;
in vec3 vCol;
in vec2 vUV;

uniform sampler2D diff0;
uniform sampler2D spec0;
uniform vec4 lightCol;
uniform vec3 lightPos;
uniform vec3 camPos;

uniform float ambience;
uniform float specular;

vec4 point(){
	vec3 lightVec = lightPos - curPos;
	float dist = length(lightVec);
	float a = 3.0f;
	float b = 0.7f;
	float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);

	vec3 normal = normalize(vNor);
	vec3 lightDir = normalize(lightVec);

	float diff = max(dot(vNor, lightDir), 0.0f);

	vec3 viewDir = normalize(camPos - curPos);
	vec3 reflectionDir = reflect(-lightDir, vNor);
	float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 8);
	float spec = specAmount * specular;

	return (texture(diff0, vUV) * (diff * intensity + ambience) + texture(spec0, vUV).r * spec * intensity) * lightCol;
}

vec4 direct(){
	vec3 normal = normalize(vNor);
	vec3 lightDir = normalize(vec3(1.0f, 1.0f, 0.0f));

	float diff = max(dot(vNor, lightDir), 0.0f);

	vec3 viewDir = normalize(camPos - curPos);
	vec3 reflectionDir = reflect(-lightDir, vNor);
	float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 8);
	float spec = specAmount * specular;

	return (texture(diff0, vUV) * (diff + ambience) + texture(spec0, vUV).r * spec) * lightCol;
}

vec4 spot(){
	float outerCone = 0.5f;
	float innerCone = 0.95f;

	// diffuse lighting
	vec3 normal = normalize(vNor);
	vec3 lightDir = normalize(lightPos - curPos);
	float diff = max(dot(normal, lightDir), 0.0f);

	// specular lighting
	vec3 viewDir = normalize(camPos - curPos);
	vec3 reflectionDir = reflect(-lightDir, vNor);
	float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 16);
	float spec = specAmount * specular;

	// calculates the intensity of the crntPos based on its angle to the center of the light cone
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDir);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diff0, vUV) * (diff * intensity + ambience) + texture(spec0, vUV).r * spec * intensity) * lightCol;
}

void main(){
	
	fCol = spot();
}