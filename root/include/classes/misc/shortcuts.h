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

	Window(int width, int height, const char* title);

	bool isValid();
	void Update();
	void Destroy();
};

struct Vertex {
	glm::vec3 pos;
};

#endif