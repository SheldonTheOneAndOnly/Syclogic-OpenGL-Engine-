#include<classes/rendering/FBO.h>

float rectVerts[] = {
		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 1.0f,

		1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f, 1.0f
};

FBO::FBO(Window window, GLint filter, GLint border) {
	glGenFramebuffers(1, &ID);
	glBindFramebuffer(GL_FRAMEBUFFER, ID);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.width, window.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, border);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, border);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
}

void FBO::Setup() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVerts), &rectVerts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void FBO::Bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void FBO::Activate(Shader& shader) {
	shader.Activate();
	glUniform1i(glGetUniformLocation(shader.ID, "screenTex"), 0);
}

void FBO::Draw() {
	glBindVertexArray(VAO);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FBO::Unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FBO::Destroy() {
	glDeleteFramebuffers(1, &ID);
}