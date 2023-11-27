#ifndef SHADER_H
#define SHADER_H

#include<string>

#include<glad.h>
#include<glfw3.h>

#include<classes/misc/Shortcuts.h>

class Shader {
public:
	GLuint ID;

	Shader(std::string name, bool hasGeo);

	void Activate();
	void Destroy();
};

#endif