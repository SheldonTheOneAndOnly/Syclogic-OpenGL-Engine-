#include<classes/rendering/VAO.h>

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::Link(VBO& VBO, GLuint layout, GLuint numComps, GLenum type, GLsizei stride, void* offset) {
	VBO.Bind();
	glVertexAttribPointer(layout, numComps, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
	std::cout << "VAO successfully created" << std::endl;
}

void VAO::Bind() {
	glBindVertexArray(ID);
}

void VAO::Unbind() {
	glBindVertexArray(0);
}

void VAO::Destroy() {
	glDeleteVertexArrays(1, &ID);
}