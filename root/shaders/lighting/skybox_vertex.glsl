#version 460 core
layout (location = 0) in vec3 aPos;

out vec3 vUV;

uniform mat4 camMat;
uniform mat4 camView;

void main(){
	vec4 pos = camMat * camView * vec4(aPos, 1.0f);
	gl_Position = pos.xyww;
	vUV = vec3(aPos.x, aPos.y, -aPos.z);
}