// Both of these libraries are very important.
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

// These libraries are classes
#include<classes/misc/Shortcuts.h>
#include<classes/core/Mesh.h>

Vertex vertices[] = {
	Vertex{glm::vec3(- 2.5f, 0.0f,  2.5f),   glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec3(0.83f, 0.70f, 0.44f), 	 glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-2.5f, 0.0f, -2.5f),    glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec3(0.83f, 0.70f, 0.44f),	 glm::vec2(0.0f, 5.0f)},
	Vertex{glm::vec3(2.5f, 0.0f, -2.5f),     glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec3(0.83f, 0.70f, 0.44f),	 glm::vec2(5.0f, 5.0f)},
	Vertex{glm::vec3(2.5f, 0.0f,  2.5f),     glm::vec3(0.0f, 1.0f, 0.0f),		glm::vec3(0.83f, 0.70f, 0.44f),	 glm::vec2(5.0f, 0.0f)},
};

// Indices for vertices order
GLuint indices[] = {
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] = {
	Vertex{glm::vec3(- 0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

int main() {
	Window window = Window(800, 800, "OpenGL Renderer");
	stbi_set_flip_vertically_on_load(true);

	Texture textures[] = {
		Texture("root/resources/textures/Brick.tga", "diff", 0, GL_RGB, GL_NEAREST, GL_REPEAT),
		Texture("root/resources/textures/Brick_s.tga", "spec", 1, GL_RED, GL_NEAREST, GL_REPEAT)
	};

	Shader shaderProg = Shader("root/shaders/basic/basic_vertex.glsl", "root/shaders/basic/basic_fragment.glsl");
	std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<GLuint> inds(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector<Texture> texs(textures, textures + sizeof(textures) / sizeof(Texture));
	Mesh plane(verts, inds, texs);

	Shader lightProg = Shader("root/shaders/lighting/light_vertex.glsl", "root/shaders/lighting/light_fragment.glsl");
	std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<GLuint> lightInds(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	Mesh light(lightVerts, lightInds, texs);
	

	glm::vec4 lightCol = glm::vec4(1.0f, 0.8f, 0.8f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.0f, 0.5f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 planePos = glm::vec3(0.0f, -0.5f, 0.0f);
	glm::mat4 planeModel = glm::mat4(1.0f);
	planeModel = glm::translate(planeModel, planePos);

	lightProg.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightProg.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightProg.ID, "lightCol"), lightCol.x, lightCol.y, lightCol.z, lightCol.w);

	shaderProg.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProg.ID, "model"), 1, GL_FALSE, glm::value_ptr(planeModel));
	glUniform4f(glGetUniformLocation(shaderProg.ID, "lightCol"), lightCol.x, lightCol.y, lightCol.z, lightCol.w);
	glUniform3f(glGetUniformLocation(shaderProg.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform1f(glGetUniformLocation(shaderProg.ID, "ambience"), 0.1f);
	glUniform1f(glGetUniformLocation(shaderProg.ID, "specular"), 0.5f);

	glEnable(GL_DEPTH_TEST);

	Camera cam(window.width, window.height, glm::vec3(0.0f, 0.0f, 2.5f));

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!glfwWindowShouldClose(window.ID)) {
		glClearColor(0.5f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam.Inputs(window.ID);
		cam.UpdateMat(70.0f, 0.1f, 100.0f);

		plane.Draw(shaderProg, cam);
		light.Draw(lightProg, cam);
		

		window.Update();
	}
	shaderProg.Destroy();
	window.Destroy();
	glfwTerminate();
	return 0;
}