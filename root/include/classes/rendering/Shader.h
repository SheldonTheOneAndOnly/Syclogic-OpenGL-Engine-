#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<cerrno>

std::string GetFileContents(const char* filename);

class Shader {
public:
	GLuint ID;

	Shader(const char* vertFile, const char* geoFile, const char* fragFile);

	void Activate();
	void Destroy();
};

#endif