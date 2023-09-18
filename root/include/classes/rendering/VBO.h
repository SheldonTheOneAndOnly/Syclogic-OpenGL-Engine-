#ifndef VBO_H
#define VBO_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<vector>

#include<classes/misc/shortcuts.h>

class VBO {
public:
	GLuint ID;

	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Destroy();
};

#endif