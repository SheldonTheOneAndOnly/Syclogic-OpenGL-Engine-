#version 460 core

out vec4 fCol;

in vec3 vCol;
in vec2 vUV;

uniform sampler2D tex0;

void main(){
	fCol = texture(tex0, vUV);
}