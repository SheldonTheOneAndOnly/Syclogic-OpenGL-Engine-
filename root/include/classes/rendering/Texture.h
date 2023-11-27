#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad.h>
#include<stb_image.h>

#include<classes/rendering/Shader.h>

class Texture {
public:
	GLuint ID;
	const char* texType;
	GLuint64 handle;

	Texture(const char* file, const char* type, GLint filter, GLint border);

	void TextureUnit(Shader& shader, const char* uni);
	void Bind();
	void Unbind();
	void Destroy();
};

#endif