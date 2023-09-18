#ifndef EBO_H
#define EBO_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<vector>

class EBO {
public:
	GLuint ID;

	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Destroy();
};

#endif