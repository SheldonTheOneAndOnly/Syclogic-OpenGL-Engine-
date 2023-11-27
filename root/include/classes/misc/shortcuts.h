#ifndef SHORTCUTS_H
#define SHORTCUTS_H

#include<iostream>
#include<fstream>
#include<sstream>
#include<cerrno>
#include<algorithm>

#include<glad.h>
#include<glfw3.h>
#include<glm/glm.hpp>

using namespace std;
using namespace glm;

string GetFileContents(const char* filename);

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

	void resize(int newWidth, int newHeight) {
		glViewport(0, 0, newWidth, newHeight);
		width = newWidth;
		height = newHeight;
		cout << width << ", " << height << endl;
	}
};

struct Vertex {
	vec3 pos;
	vec3 col;
	vec2 UV;
	vec3 nor;
};

static float SmoothStep(float x, float p1, float p2);

#endif