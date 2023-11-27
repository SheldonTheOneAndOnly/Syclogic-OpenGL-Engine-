#include<classes/rendering/VBO.h>

VBO::VBO(std::vector<Vertex>& verts, GLenum usage) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), usage);
	std::cout << "VBO successfully created" << std::endl;
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Destroy() {
	glDeleteBuffers(1, &ID);
}