#version 460 core

out vec4 fCol;
in vec2 vUV;

uniform sampler2D screenTex;

void main(){
	fCol = texture(screenTex, vUV);
}