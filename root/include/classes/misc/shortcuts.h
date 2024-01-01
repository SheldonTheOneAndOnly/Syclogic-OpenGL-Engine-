#ifndef SHORTCUTS_H
#define SHORTCUTS_H

#include<iostream>
#include<fstream>
#include<sstream>
#include<cerrno>
#include<algorithm>

#include<glad.h>
#include<glfw3.h>
#include<glfw3native.h>
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
	void Frame(string filename);
	void DrawFrame();
	void Update();

	void ChangeTitle(string title);

	void Destroy();

private:
	float lastFrame, curFrame = 0.0f;
	int WINDOW_FRAME_MARGIN_SIZE = 16;
	int WINDOW_FRAME_INNER_SIZE = 32;

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