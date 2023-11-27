#ifndef VBO_H
#define VBO_H

#include<glad.h>
#include<glfw3.h>
#include<vector>

#include<classes/misc/shortcuts.h>

class VBO {
public:
	GLuint ID;

	VBO(std::vector<Vertex>& verts, GLenum usage);

	void Bind();
	void Unbind();
	void Destroy();
};

#endif