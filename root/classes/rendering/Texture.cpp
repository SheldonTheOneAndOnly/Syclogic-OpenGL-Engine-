#include<classes/rendering/Texture.h>
Texture::Texture(const char* file, GLenum type, GLenum textureNum, GLint format, GLint filter, GLint border) {
	int width, height, numColCh;
	unsigned char* bytes = stbi_load(file, &width, &height, &numColCh, 0);

	glGenTextures(1, &ID);
	glActiveTexture(textureNum);
	glBindTexture(type, ID);

	texType = type;

	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, filter);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, border);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, border);

	glTexImage2D(type, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(type);

	stbi_image_free(bytes);
	glBindTexture(type, 0);
}

void Texture::TextureUnit(Shader& shader, const char* uni, GLuint unit) {
	GLuint texUni = glGetUniformLocation(shader.ID, uni);
	shader.Activate();
	glUniform1f(texUni, unit);
}

void Texture::Bind() {
	glBindTexture(texType, ID);
}

void Texture::Unbind() {
	glBindTexture(texType, 0);
}

void Texture::Destroy() {
	glDeleteTextures(1, &ID);
}