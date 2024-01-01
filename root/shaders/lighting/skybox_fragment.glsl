#version 460 core
#extension GL_ARB_bindless_texture: require

out vec4 fCol;

in vec3 vUV;

layout(bindless_sampler) uniform samplerCube skybox;

void main(){
	fCol = texture(skybox, vUV);
}