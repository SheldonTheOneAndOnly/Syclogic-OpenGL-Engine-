#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aNor;

out vec3 vNor;
out vec3 vRefNor;
out vec2 vUV;

uniform mat4 projection, view, model;
uniform vec3 lightPos;
uniform vec3 camPos;

void main(){
	vUV = mat2(0.0, -1.0, 1.0, 0.0) * aUV;
	vNor = aNor;
	
	vec4 worldPos = model * vec4(aPos, 1.0f);
	gl_Position = projection * view * worldPos;

	vec3 viewVec = normalize(worldPos.xyz - camPos);
	vRefNor = reflect(viewVec, aNor);
}