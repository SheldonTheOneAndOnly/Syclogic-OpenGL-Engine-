#include<classes/rendering/Texture.h>
Texture::Texture(const char* file, const char* type, GLuint slot, GLint filter, GLint border) {
	int width, height, numColCh;
	unsigned char* bytes = stbi_load(file, &width, &height, &numColCh, 0);

	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	texType = type;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, border);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, border);

	if (numColCh == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	}
	else if (numColCh == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	}
	else if (numColCh == 1) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::TextureUnit(Shader& shader, const char* uni, GLuint unit) {
	GLuint texUni = glGetUniformLocation(shader.ID, uni);
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind() {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Destroy() {
	glDeleteTextures(1, &ID);
}