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
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

GLuint indices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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

	Camera cam(window.width, window.height, glm::vec3(0.0f, 0.0f, 2.5f));

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!glfwWindowShouldClose(window.ID)) {
		glClearColor(0.5f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProg.Activate();

		cam.Inputs(window.ID);
		cam.UpdateMat(70, 0.1f, 100.0f);
		cam.Mat(shaderProg, "camMat");

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