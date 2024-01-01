#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aUV;
layout (location = 3) in vec3 aNor;

out DATA {
	vec3 vNor;
	vec3 vRefNor;
	vec3 vCol;
	vec2 vUV;
	mat4 camMat;
	mat4 model;
	vec3 lightPos;
	vec3 camPos;
} data_out;

uniform mat4 projection, view, model;
uniform vec3 lightPos;
uniform vec3 camPos;

void main(){
	data_out.vCol = aCol;
	data_out.vUV = mat2(0.0, -1.0, 1.0, 0.0) * aUV;
	data_out.vNor = aNor;
	data_out.camMat = projection * view;
	data_out.model = model;
	data_out.lightPos = lightPos;
	data_out.camPos = camPos;
	
	vec4 modelPos = model * vec4(aPos, 1.0f);
	gl_Position = modelPos;

	vec3 viewVec = modelPos.xyz - camPos;
	data_out.vRefNor = reflect(viewVec, aNor);
}