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
#include<classes/rendering/Shader.h>
#include<classes/rendering/VAO.h>
#include<classes/rendering/VBO.h>	
#include<classes/rendering/EBO.h>
#include<classes/rendering/Texture.h>
#include<classes/rendering/Camera.h>

GLfloat vertices[] = {
	-0.5f, 0.0f,  0.5f,     0.0f, 1.0f, 0.0f,	0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.0f, 1.0f, 0.0f,	0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,
	 0.5f, 0.0f, -0.5f,     0.0f, 1.0f, 0.0f,	0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,
	 0.5f, 0.0f,  0.5f,     0.0f, 1.0f, 0.0f,	0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,
};

// Indices for vertices order
GLuint indices[] = {
	0, 1, 2,
	0, 2, 3
};

GLfloat lightVertices[] = {
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
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

	Shader shaderProg = Shader("root/shaders/basic/basic_vertex.glsl", "root/shaders/basic/basic_fragment.glsl");
	VAO basicVAO;
	basicVAO.Bind();

	VBO basicVBO(vertices, sizeof(vertices));
	EBO basicEBO(indices, sizeof(indices));

	basicVAO.Link(basicVBO, 0, 3, GL_FLOAT, 11 * sizeof(float), 0);
	basicVAO.Link(basicVBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	basicVAO.Link(basicVBO, 2, 3, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	basicVAO.Link(basicVBO, 3, 2, GL_FLOAT, 11 * sizeof(float), (void*)(9 * sizeof(float)));
	basicVAO.Unbind();
	basicVBO.Unbind();
	basicEBO.Unbind();

	Shader lightProg = Shader("root/shaders/lighting/point_vertex.glsl", "root/shaders/lighting/point_fragment.glsl");
	VAO lightVAO;
	lightVAO.Bind();

	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	lightVAO.Link(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightCol = glm::vec4(1.0f, 0.8f, 0.8f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.0f, 1.0f, 0.0f);
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
	glUniform1f(glGetUniformLocation(shaderProg.ID, "ambience"), 0.25f);
	glUniform1f(glGetUniformLocation(shaderProg.ID, "specular"), 0.5f);

	Texture texture("root/resources/textures/Brick.tga", GL_TEXTURE_2D, 0, GL_RGB, GL_NEAREST, GL_REPEAT);
	texture.TextureUnit(shaderProg, "tex0", 0);

	Texture specularMap("root/resources/textures/Brick_s.tga", GL_TEXTURE_2D, 1, GL_RED, GL_NEAREST, GL_REPEAT);
	specularMap.TextureUnit(shaderProg, "tex1", 1);

	glEnable(GL_DEPTH_TEST);

	Camera cam(window.width, window.height, glm::vec3(0.0f, 0.0f, 2.5f));

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!glfwWindowShouldClose(window.ID)) {
		glClearColor(0.5f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProg.Activate();
		glUniform3f(glGetUniformLocation(shaderProg.ID, "camPos"), cam.position.x, cam.position.y, cam.position.z);
		cam.Inputs(window.ID);
		cam.UpdateMat(70, 0.1f, 100.0f);
		cam.Mat(shaderProg, "camMat");

		texture.Bind();
		specularMap.Bind();
		basicVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		lightProg.Activate();
		cam.Mat(lightProg, "camMat");
		lightVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		window.Update();
	}
	texture.Destroy();
	basicVAO.Destroy();
	basicVBO.Destroy();
	basicEBO.Destroy();
	shaderProg.Destroy();
	window.Destroy();
	glfwTerminate();
	return 0;
}