#version 460 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 vNor;
out vec3 vCol;
out vec2 vUV;
out vec3 curPos;
out vec3 lightPos;
out vec3 camPos;

in DATA {
	vec3 vNor;
	vec3 vCol;
	vec2 vUV;
	mat4 camMat;
	mat4 model;
	vec3 lightPos;
	vec3 camPos;
} data_in[];

void main(){
	// Normal Mapping
	vec3 edge0 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 edge1 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec2 deltaUV0 = data_in[1].vUV - data_in[0].vUV;
	vec2 deltaUV1 = data_in[2].vUV - data_in[0].vUV;

	float f = 1.0f / (deltaUV0.x * deltaUV1.y - deltaUV0.y * deltaUV1.x);

	vec3 tang = vec3(f * (deltaUV1.y * edge0 - deltaUV0.y * edge1));
	vec3 bitang = vec3(f * (-deltaUV1.x * edge0 + deltaUV0.x * edge1));
	
	vec3 t = normalize(vec3(data_in[0].model * vec4(tang, 0.0f)));
	vec3 b = normalize(vec3(data_in[0].model * vec4(bitang, 0.0f)));
	vec3 n = normalize(vec3(data_in[0].model * vec4(cross(edge1, edge0), 0.0f)));

	mat3 tbn = mat3(t, b, n);
	tbn = transpose(tbn);

	// Basic
	gl_Position = data_in[0].camMat * gl_in[0].gl_Position;
	vNor = tbn * data_in[0].vNor;
	vCol = data_in[0].vCol;
	vUV = data_in[0].vUV;
	curPos = tbn * gl_in[0].gl_Position.xyz;
	lightPos = tbn * data_in[0].lightPos;
	camPos = tbn * data_in[0].camPos;
	EmitVertex();
	
	gl_Position = data_in[1].camMat * gl_in[1].gl_Position;
	vNor = tbn * data_in[1].vNor;
	vCol = data_in[1].vCol;
	vUV = data_in[1].vUV;
	curPos = tbn * gl_in[1].gl_Position.xyz;
	lightPos = tbn * data_in[1].lightPos;
	camPos = tbn * data_in[1].camPos;
	EmitVertex();
	
	gl_Position = data_in[2].camMat * gl_in[2].gl_Position;
	vNor = tbn * data_in[2].vNor;
	vCol = data_in[2].vCol;
	vUV = data_in[2].vUV;
	curPos = tbn * gl_in[2].gl_Position.xyz;
	lightPos = tbn * data_in[2].lightPos;
	camPos = tbn * data_in[2].camPos;
	EmitVertex();

	EndPrimitive();
}