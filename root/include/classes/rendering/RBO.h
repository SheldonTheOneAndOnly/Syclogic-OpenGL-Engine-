#ifndef RBO_H
#define RBO_H

#include<string>

#include<glad.h>
#include<glfw3.h>

#include<classes/misc/Shortcuts.h>

class RBO {
public:
	GLuint ID;

	RBO(Window window);

	void Apply();
	void Bind();
	void Unbind();
	void Destroy();
};

#endif