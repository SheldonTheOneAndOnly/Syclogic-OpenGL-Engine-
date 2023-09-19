#version 460 core

out vec4 fCol;

uniform vec4 lightCol;

void main(){
	fCol = lightCol;
}