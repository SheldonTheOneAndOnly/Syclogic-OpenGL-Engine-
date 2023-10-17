#ifndef SHORTCUTS_H
#define SHORTCUTS_H

#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

class Window
{
public:
	bool initialized = false;
	GLFWwindow* ID;
	int width, height;

	Window(int windowWidth, int windowHeight, const char* title, unsigned int samples);

	bool isValid();
	void Update();
	void Destroy();
};

struct Vertex {
	glm::vec3 pos;
	glm::vec3 col;
	glm::vec2 UV;
	glm::vec3 nor;
};

#endif