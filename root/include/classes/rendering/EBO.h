#ifndef EBO_H
#define EBO_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<vector>

class EBO {
public:
	GLuint ID;

	EBO(std::vector<GLuint>& inds);

	void Bind();
	void Unbind();
	void Destroy();
};

#endif