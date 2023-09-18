// Both of these libraries are very important.
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

// These libraries are classes
#include<classes/misc/shortcuts.h>
#include<classes/rendering/Shader.h>
#include<classes/rendering/VAO.h>
#include<classes/rendering/VBO.h>
#include<classes/rendering/EBO.h>

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
	0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
	-0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
	0.5f, 0.5f, 0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f
};

GLuint indices[] = {
	0, 1, 2,
	1, 3, 2
};

int main() {
	Window window = Window(800, 600, "OpenGL Renderer");

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

	stbi_set_flip_vertically_on_load(true);

	int width, height, numColCh;
	unsigned char* bytes = stbi_load("root/resources/textures/Got.png", &width, &height, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shaderProg.ID, "tex0");
	shaderProg.Activate();
	glUniform1i(tex0Uni, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!glfwWindowShouldClose(window.ID)) {
		glClearColor(0.5f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProg.Activate();
		glBindTexture(GL_TEXTURE_2D, texture);
		VAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		window.Update();
	}
	VAO.Destroy();
	VBO.Destroy();
	EBO.Destroy();
	shaderProg.Destroy();
	window.Destroy();
	glfwTerminate();
	return 0;
}