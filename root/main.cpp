// Both of these libraries are very important.
#include<iostream>
#include<glad.h>
#include<glfw3.h>
#include<stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

// These libraries are classes
#include<classes/misc/Shortcuts.h>
#include<classes/rendering/skybox.h>
#include<classes/core/Model.h>
#include<classes/rendering/UI.h>
#include<classes/rendering/Material.h>

Vertex vertices[] = {
	Vertex{glm::vec3(- 1.0f, 0.0f,  1.0f),   glm::vec3(1.0f, 1.0f, 1.0f),	 glm::vec2(0.0f, 0.0f),		glm::vec3(0.0f, 1.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f),    glm::vec3(1.0f, 1.0f, 1.0f),	 glm::vec2(0.0f, 2.0f),		glm::vec3(0.0f, 1.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f, -1.0f),     glm::vec3(1.0f, 1.0f, 1.0f),	 glm::vec2(2.0f, 2.0f),		glm::vec3(0.0f, 1.0f, 0.0f)},
	Vertex{glm::vec3(1.0f, 0.0f,  1.0f),     glm::vec3(1.0f, 1.0f, 1.0f),	 glm::vec2(2.0f, 0.0f),		glm::vec3(0.0f, 1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] = {
	0, 1, 2,
	0, 2, 3
};

float FOV = 70.0f;
float targetFOV = FOV;
void scroll(GLFWwindow* w, double x, double y) {
	targetFOV += y * 2;
	targetFOV = clamp(targetFOV, 15.0f, 150.0f);
}

int main() {
	Window window = Window(800, 600, "Syclogic 0.12", 8);

	stbi_set_flip_vertically_on_load(true);
	Material grass("root/resources/textures/test/grass.sycmat");

	Shader shaderProg("root/shaders/basic/basic", true);
	Shader cubeProg("root/shaders/assets/test", true);
	Shader textProg("root/shaders/UI/text", false);
	Shader normalsProg("root/shaders/debug/normals", true);
	std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<GLuint> inds(indices, indices + sizeof(indices) / sizeof(GLuint));
	Mesh plane(verts, inds, grass.textures);

	glm::vec4 lightCol = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 planePos = glm::vec3(0.0f, -0.5f, 0.0f);
	glm::mat4 planeModel = glm::mat4(1.0f);
	planeModel = glm::translate(planeModel, planePos);

	shaderProg.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProg.ID, "model"), 1, GL_FALSE, glm::value_ptr(planeModel));
	glUniform4f(glGetUniformLocation(shaderProg.ID, "lightCol"), lightCol.x, lightCol.y, lightCol.z, lightCol.w);
	glUniform3f(glGetUniformLocation(shaderProg.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform1f(glGetUniformLocation(shaderProg.ID, "ambience"), 0.1f);
	glUniform1f(glGetUniformLocation(shaderProg.ID, "specular"), 1.0f);
	glUniform1f(glGetUniformLocation(shaderProg.ID, "height"), 0.1f);

	cubeProg.Activate();
	glUniformMatrix4fv(glGetUniformLocation(cubeProg.ID, "model"), 1, GL_FALSE, glm::value_ptr(planeModel));
	glUniform4f(glGetUniformLocation(cubeProg.ID, "lightCol"), lightCol.x, lightCol.y, lightCol.z, lightCol.w);
	glUniform3f(glGetUniformLocation(cubeProg.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(cubeProg.ID, "lightAng"), 0.0f, 0.0f, -1.0f);
	glUniform1i(glGetUniformLocation(cubeProg.ID, "lightType"), 1);

	glUniform1f(glGetUniformLocation(cubeProg.ID, "atten_a"), 1.0f);
	glUniform1f(glGetUniformLocation(cubeProg.ID, "atten_b"), 0.5f);

	glUniform1f(glGetUniformLocation(cubeProg.ID, "ambience"), 0.1f);
	glUniform1f(glGetUniformLocation(cubeProg.ID, "specular"), 0.5f);
	glUniform1f(glGetUniformLocation(cubeProg.ID, "metallic"), 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	Skybox skybox("storforsen.jpg");
	glUniformHandleui64ARB(glGetUniformLocation(cubeProg.ID, "skybox"), skybox.handle);

	Camera cam(window.width, window.height, vec3(0.0f, 0.0f, 2.5f));
	glfwSetScrollCallback(window.ID, scroll);

	Text text("root/resources/fonts/helvetica.ttf");

	glPolygonMode(GL_FRONT, GL_FILL);

	system("CLS");
	std::cout << R"(   _____            _             _      
  / ____|          | |           (_)     
 | (___  _   _  ___| | ___   __ _ _  ___ 
  \___ \| | | |/ __| |/ _ \ / _` | |/ __|
  ____) | |_| | (__| | (_) | (_| | | (__ 
 |_____/ \__, |\___|_|\___/ \__, |_|\___|
          __/ |              __/ |       
         |___/              |___/        )" << endl << "\t\tAn OpenGL engine by Syclon!" << endl << endl << "Version 0.12 (Skybox!)" << endl << endl << "New features:\n*Skyboxes* can be created\nVSync!\nSmooth mouse control!";

	float t = 0.0f;
	bool nmt = false;
	bool smt = false;
	bool isHoldingN = false;
	bool isHoldingM = false;
	glfwSwapInterval(1);
	while (!glfwWindowShouldClose(window.ID)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		FOV = FOV * (1.0f - window.deltaTime / 0.1f) + targetFOV * window.deltaTime / 0.1f;
		cam.Inputs(window.ID, window.deltaTime);
		cam.UpdateMat(window.width, window.height, FOV, 0.1f, 100.0f);

		cubeProg.Activate();

		mat4 ortho = glm::ortho(0.0f, static_cast<float>(window.width), 0.0f, static_cast<float>(window.height));

		glUniformMatrix4fv(glGetUniformLocation(cubeProg.ID, "projection"), 1, GL_FALSE, value_ptr(cam.projection));
		glUniformMatrix4fv(glGetUniformLocation(cubeProg.ID, "view"), 1, GL_FALSE, value_ptr(cam.view));
		glUniformMatrix4fv(glGetUniformLocation(textProg.ID, "projection"), 1, GL_FALSE, value_ptr(ortho));
		//glUniform3f(glGetUniformLocation(shaderProg.ID, "lightPos"), lightPos.x + sinf(t) / 2, lightPos.y, lightPos.z + cosf(t) / 2);
		//glUniform3f(glGetUniformLocation(cubeProg.ID, "lightPos"), cam.position.x, cam.position.y, cam.position.z);
		//glUniform3f(glGetUniformLocation(cubeProg.ID, "lightAng"), cam.angle.x, cam.angle.y, cam.angle.z);

		if (glfwGetKey(window.ID, GLFW_KEY_N) == GLFW_PRESS && !isHoldingN) {
			isHoldingN = true;
			nmt = !nmt;
		}
		else if (glfwGetKey(window.ID, GLFW_KEY_N) == GLFW_RELEASE) isHoldingN = false;

		if (glfwGetKey(window.ID, GLFW_KEY_M) == GLFW_PRESS && !isHoldingM) {
			isHoldingM = true;
			smt = !smt;
		}
		else if (glfwGetKey(window.ID, GLFW_KEY_M) == GLFW_RELEASE) isHoldingM = false;

		glUniform1i(glGetUniformLocation(cubeProg.ID, "normalMappingToggle"), nmt);
		glUniform1i(glGetUniformLocation(cubeProg.ID, "specularMappingToggle"), smt);

		plane.Draw(cubeProg, cam);
		skybox.Draw(cam);

		window.Update();

		window.ChangeTitle("Syclogic 0.12 (" + to_string((int)round(1.0f / window.deltaTime)) + ")");
	}
	shaderProg.Destroy();
	window.Destroy();
	glfwTerminate();
	return 0;
}