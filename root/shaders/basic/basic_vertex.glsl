#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
layout (location = 2) in vec3 aCol;
layout (location = 3) in vec2 aUV;

out DATA {
	vec3 curPos;
	vec3 vNor;
	vec3 vCol;
	vec2 vUV;
	mat4 camMat;
} data_out;

uniform mat4 camMat;
uniform mat4 model;

void main(){
	data_out.curPos = vec3(model * vec4(aPos, 1.0f));
	data_out.vCol = aCol;
	data_out.vUV = mat2(0.0, -1.0, 1.0, 0.0) * aUV;
	data_out.vNor = aNor;
	data_out.camMat = camMat;
	
	gl_Position = camMat * vec4(data_out.curPos, 1.0f);
}