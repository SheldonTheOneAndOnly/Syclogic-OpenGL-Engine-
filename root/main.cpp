// Both of these libraries are very important.
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

// These libraries are classes
#include<classes/misc/shortcuts.h>
#include<classes/rendering/Shader.h>
#include<classes/rendering/VAO.h>
#include<classes/rendering/VBO.h>
#include<classes/rendering/EBO.h>
#include<classes/rendering/Texture.h>

GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	0.0f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,		0.5f, 0.0f,
	0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f,		0.5f, 1.0f
};

GLuint indices[] = {
	0, 1, 2,
	0, 1, 3,
	1, 2, 3,
	2, 0, 3
};

int main() {
	Window window = Window(800, 600, "OpenGL Renderer");
	stbi_set_flip_vertically_on_load(true);

	Shader shaderProg = Shader("root/shaders/basic/basic_vertex.glsl", "root/shaders/basic/basic_fragment.glsl");
	VAO VAO;
	VAO.Bind();

	VBO VBO(vertices, sizeof(vertices));
	EBO EBO(indices, sizeof(indices));

	VAO.Link(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), 0);
	VAO.Link(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO.Link(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

	Texture texture("root/resources/textures/Got.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_NEAREST, GL_REPEAT);
	texture.TextureUnit(shaderProg, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	while (!glfwWindowShouldClose(window.ID)) {
		glClearColor(0.5f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProg.Activate();

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60) {
			rotation += 0.5f;
			prevTime = crntTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.5f));
		proj = glm::perspective(glm::radians(70.0f), (float)(window.width / window.height), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProg.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(shaderProg.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projLoc = glGetUniformLocation(shaderProg.ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		texture.Bind();
		VAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		window.Update();
	}
	texture.Destroy();
	VAO.Destroy();
	VBO.Destroy();
	EBO.Destroy();
	shaderProg.Destroy();
	window.Destroy();
	glfwTerminate();
	return 0;
}