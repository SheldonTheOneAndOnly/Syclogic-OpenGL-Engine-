#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include<classes/rendering/Shader.h>

class Texture {
public:
	GLuint ID;
	GLenum texType;

	Texture(const char* file, GLenum type, GLenum textureNum, GLint format, GLint filter, GLint border);

	void TextureUnit(Shader& shader, const char* uni, GLuint unit);
	void Bind();
	void Unbind();
	void Destroy();
};

#endif