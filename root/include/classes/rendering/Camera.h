#ifndef CAMERA_H
#define CAMERA_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include<classes/rendering/shader.h>

class Camera {
public:
	glm::vec3 position;
	glm::vec3 angle = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 camMat = glm::mat4(1.0f);

	bool debounce = false;

	int width, height;

	float speed = 0.01f;
	float sensitivity = 100.0f;

	Camera(int Width, int Height, glm::vec3 Pos);

	void UpdateMat(float FOV, float nearZ, float farZ);
	void Mat(Shader& shader, const char* uni);
	void Inputs(GLFWwindow* window, float deltaTime);
private:
	glm::vec3 direction;
	float multiplySpeed = 0.0f;
};

#endif