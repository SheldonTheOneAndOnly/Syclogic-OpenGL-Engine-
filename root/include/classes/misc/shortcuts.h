#ifndef SHORTCUTS_H
#define SHORTCUTS_H

#include<iostream>
#include<fstream>
#include<sstream>
#include<cerrno>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

std::string GetFileContents(const char* filename);

class Window
{
public:
	bool initialized = false;
	GLFWwindow* ID;
	int width, height;
	float deltaTime = 0.0f;

	Window(int windowWidth, int windowHeight, const char* title, unsigned int samples);

	bool isValid();
	void Update();
	void Destroy();

private:
	float lastFrame = 0.0f;
	float curFrame = 0.0f;
};

struct Vertex {
	glm::vec3 pos;
	glm::vec3 col;
	glm::vec2 UV;
	glm::vec3 nor;
};

#endif