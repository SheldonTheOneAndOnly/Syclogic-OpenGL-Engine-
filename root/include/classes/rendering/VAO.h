#ifndef VAO_H
#define VAO_H

#include<glad.h>
#include<glfw3.h>

#include<classes/rendering/VBO.h>

class VAO {
public:
	GLuint ID;

	VAO();

	void Link(VBO& VBO, GLuint layout, GLuint numComps, GLenum type, GLsizei stride, void* offset);
	void Bind();
	void Unbind();
	void Destroy();
};

#endif