#include<classes/rendering/VAO.h>

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::Link(VBO VBO, GLuint layout) {
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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