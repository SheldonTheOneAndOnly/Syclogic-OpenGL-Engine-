#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;
layout (location = 2) in vec3 aCol;
layout (location = 3) in vec2 aUV;

out vec3 vNor;
out vec3 curPos;
out vec3 vCol;
out vec2 vUV;

uniform mat4 camMat;
uniform mat4 model;

void main(){
	curPos = vec3(model * vec4(aPos, 1.0f));

	gl_Position = camMat * vec4(curPos, 1.0f);
	vCol = aCol;
	vUV = aUV;
	vNor = aNor;
}