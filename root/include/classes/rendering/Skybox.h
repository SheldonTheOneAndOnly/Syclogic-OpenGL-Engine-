#ifndef SKYBOX_H
#define SKYBOX_H

#include<iostream>
#include<string>

#include<glad.h>
#include<glfw3.h>
#include<stb_image.h>
#include<glm/gtc/matrix_transform.hpp>

#include<classes/misc/Shortcuts.h>
#include<classes/rendering/Shader.h>
#include<classes/rendering/VAO.h>
#include<classes/rendering/VBO.h>
#include<classes/rendering/EBO.h>
#include<classes/rendering/Camera.h>

using namespace std;
using namespace glm;

class Skybox {
public:
	GLuint ID;
	GLuint64 handle;

	Skybox(string name);
	void Draw(Camera cam);

private:
	Vertex verts[8] = {
		Vertex{vec3(-1.0f, -1.0f, 1.0f)},
		Vertex{vec3(1.0f, -1.0f, 1.0f)},
		Vertex{vec3(1.0f, -1.0f, -1.0f)},
		Vertex{vec3(-1.0f, -1.0f, -1.0f)},
		Vertex{vec3(-1.0f, 1.0f, 1.0f)},
		Vertex{vec3(1.0f, 1.0f, 1.0f)},
		Vertex{vec3(1.0f, 1.0f, -1.0f)},
		Vertex{vec3(-1.0f, 1.0f, -1.0f)}
	};

	unsigned int inds[36] = {
		1, 2, 6,
		6, 5, 1,

		0, 4, 7,
		7, 3, 0,

		4, 5, 6,
		6, 7, 4,

		0, 3, 2,
		2, 1, 0,

		0, 1, 5,
		5, 4, 0,

		3, 7, 6,
		6, 2, 3
	};

	Shader shader;
	VAO VAO;
};

#endif