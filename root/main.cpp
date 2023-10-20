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
#include<classes/core/Model.h>

Vertex vertices[] = {
	Vertex{glm::vec3(- 1.0f, 0.0f,  1.0f),   glm::vec3(1.0f, 1.0f, 1.0f),	 glm::vec2(0.0f, 0.0f),		glm::vec3(0.0f, 1.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f),    glm::vec3(1.0f, 1.0f, 1.0f),	 glm::vec2(0.0f, 1.0f),		glm::vec3(0.0f, 1.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f),     glm::vec3(1.0f, 1.0f, 1.0f),	 glm::vec2(1.0f, 1.0f),		glm::vec3(0.0f, 1.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f),     glm::vec3(1.0f, 1.0f, 1.0f),	 glm::vec2(1.0f, 0.0f),		glm::vec3(0.0f, 1.0f, 0.0f)}
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
	Window window = Window(800, 800, "OpenGL Renderer", 8);
	stbi_set_flip_vertically_on_load(true);

	Texture textures[] = {
		Texture("root/resources/textures/AICobblestone.png", "diff", 0, GL_LINEAR, GL_REPEAT),
		Texture("root/resources/textures/AICobblestone_s.png", "spec", 1, GL_LINEAR, GL_REPEAT),
		Texture("root/resources/textures/AICobblestone_nh.png", "norm", 2, GL_LINEAR, GL_REPEAT)
	};

	Shader shaderProg("root/shaders/basic/basic", true);
	std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<GLuint> inds(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector<Texture> texs(textures, textures + sizeof(textures) / sizeof(Texture));
	Mesh plane(verts, inds, texs);

	Shader lightProg("root/shaders/lighting/light", false);
	std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<GLuint> lightInds(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	Mesh light(lightVerts, lightInds, texs);

	Model plane2("root/resources/models/plane.syc");

	glm::vec4 lightCol = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
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
	glUniform1f(glGetUniformLocation(shaderProg.ID, "specular"), 1.0f);
	glUniform1f(glGetUniformLocation(shaderProg.ID, "height"), 0.1f);
	glUniform1i(glGetUniformLocation(shaderProg.ID, "normalMappingToggle"), 1);
	glUniform1i(glGetUniformLocation(shaderProg.ID, "parallaxMappingToggle"), 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	Camera cam(window.width, window.height, glm::vec3(0.0f, 0.0f, 2.5f));

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	system("CLS");
	cout << R"(   _____            _             _      
  / ____|          | |           (_)     
 | (___  _   _  ___| | ___   __ _ _  ___ 
  \___ \| | | |/ __| |/ _ \ / _` | |/ __|
  ____) | |_| | (__| | (_) | (_| | | (__ 
 |_____/ \__, |\___|_|\___/ \__, |_|\___|
          __/ |              __/ |       
         |___/              |___/        )" << endl << "Version 0.10 (.syc files!)" << endl;

	while (!glfwWindowShouldClose(window.ID)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam.Inputs(window.ID, window.deltaTime);
		cam.UpdateMat(70.0f, 0.1f, 100.0f);

		plane2.Draw(shaderProg, cam);
		light.Draw(lightProg, cam);

		window.Update();
	}
	shaderProg.Destroy();
	window.Destroy();
	glfwTerminate();
	return 0;
}