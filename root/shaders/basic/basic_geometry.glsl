#version 460 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 curPos;
out vec3 vNor;
out vec3 vCol;
out vec2 vUV;

in DATA {
	vec3 curPos;
	vec3 vNor;
	vec3 vCol;
	vec2 vUV;
	mat4 camMat;
} data_in[];

void main(){
	curPos = data_in[0].curPos;
	gl_Position = gl_in[0].gl_Position;
	vNor = data_in[0].vNor;
	vCol = data_in[0].vCol;
	vUV = data_in[0].vUV;
	EmitVertex();
	
	curPos = data_in[1].curPos;
	gl_Position = gl_in[1].gl_Position;
	vNor = data_in[1].vNor;
	vCol = data_in[1].vCol;
	vUV = data_in[1].vUV;
	EmitVertex();
	
	curPos = data_in[2].curPos;
	gl_Position = gl_in[2].gl_Position;
	vNor = data_in[2].vNor;
	vCol = data_in[2].vCol;
	vUV = data_in[2].vUV;
	EmitVertex();

	EndPrimitive();
}