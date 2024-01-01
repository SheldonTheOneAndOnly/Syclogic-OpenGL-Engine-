#ifndef CAMERA_H
#define CAMERA_H

#include<glad.h>
#include<glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include<glm/gtx/string_cast.hpp>

#include<classes/rendering/shader.h>

class Camera {
public:
	glm::vec3 position;
	glm::vec3 angle = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 projection, view = glm::mat4(1.0f);
	glm::mat4 camMat = glm::mat4(1.0f);

	bool debounce = false;

	int width, height;
	float FOV, nearZ, farZ;

	float speed = 1.0f;
	float sensitivity = 100.0f;

	Camera(int width, int height, glm::vec3 Pos);

	void UpdateMat(int width, int height, float FOV, float nearZ, float farZ);
	void Mat(Shader& shader);
	void Inputs(GLFWwindow* window, float deltaTime);
private:
	vec3 lerpPos = vec3(0.0f);
	vec2 lerpRot = vec2(0.0f);

	float rotX = 0.0f;
	float rotY = 0.0f;

	float multiplySpeed = 1.0f;

	int movementKeys[6] = {
		GLFW_KEY_W,
		GLFW_KEY_S,
		GLFW_KEY_A,
		GLFW_KEY_S,
		GLFW_KEY_SPACE,
		GLFW_KEY_LEFT_CONTROL,
	};

	float lerp(float x, float y, float t) {
		return x * (1.0f - t) + y * t;
	}
	
	vec3 vec3Lerp(vec3 x, vec3 y, float t) {
		return x * (1.0f - t) + y * t;
	}
};

#endif