#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include<classes/rendering/Shader.h>

class Texture {
public:
	GLuint ID;
	const char* texType;
	GLuint unit;

	Texture(const char* file, const char* type, GLuint slot, GLint filter, GLint border);

	void TextureUnit(Shader& shader, const char* uni, GLuint unit);
	void Bind();
	void Unbind();
	void Destroy();
};

#endif