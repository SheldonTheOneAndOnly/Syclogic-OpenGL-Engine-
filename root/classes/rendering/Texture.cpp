#include<classes/rendering/Texture.h>
Texture::Texture(const char* file, const char* type, GLint filter, GLint border) {
	int width, height, numColCh;
	unsigned char* bytes = stbi_load(file, &width, &height, &numColCh, 0);

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	texType = type;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, border);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, border);

	if (numColCh == 4) { // RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	}
	else if (numColCh == 3) { // RGB
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	}
	else if (numColCh == 1) { // Grayscale
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
	}
	glGenerateMipmap(GL_TEXTURE_2D);
	handle = glGetTextureHandleARB(ID);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::TextureUnit(Shader& shader, const char* uni) {
	GLuint texUni = glGetUniformLocation(shader.ID, uni);
	shader.Activate();
	glUniformHandleui64ARB(texUni, handle);
}

void Texture::Bind() {
	glMakeTextureHandleResidentARB(handle);
}

void Texture::Unbind() {
	glMakeTextureHandleNonResidentARB(handle);
}

void Texture::Destroy() {
	glDeleteTextures(1, &ID);
}