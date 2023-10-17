#ifndef FBO_H
#define FBO_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<classes/core/Mesh.h>

class FBO {
public:
	GLuint ID;
	GLuint textureID;

	unsigned int VAO, VBO;

	FBO(Window window, GLint filter, GLint border);

	void Setup();
	void Activate(Shader& shader);
	void Draw();
	void Bind();
	void Unbind();
	void Destroy();
};

#endif