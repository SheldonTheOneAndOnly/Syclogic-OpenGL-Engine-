#include<classes/rendering/Camera.h>

Camera::Camera(int Width, int Height, glm::vec3 Pos) {
	width = Width;
	height = Height;
	position = Pos;
	lerpPos = position;
}

void Camera::UpdateMat(int w, int h, float FOV, float nearZ, float farZ) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(position, position + angle, upDirection);
	projection = glm::perspective(glm::radians(FOV), (float)w / h, nearZ, farZ);

	camMat = projection * view;

	width = w;
	height = h;
}

void Camera::Mat(Shader& shader, const char* uni) {
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uni), 1, GL_FALSE, glm::value_ptr(camMat));
}

void Camera::Inputs(GLFWwindow* window, float deltaTime) {
	// Movement

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		lerpPos += (speed * multiplySpeed * angle) * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		lerpPos += (speed * multiplySpeed * -angle) * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		lerpPos += (speed * multiplySpeed * -glm::normalize(glm::cross(angle, upDirection))) * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		lerpPos += (speed * multiplySpeed * glm::normalize(glm::cross(angle, upDirection))) * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		lerpPos += (speed * multiplySpeed * upDirection) * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		lerpPos += (speed * multiplySpeed * -upDirection) * deltaTime;
	}

	position = vec3Lerp(position, lerpPos, deltaTime / 0.1f);

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		multiplySpeed = Camera::lerp(multiplySpeed, 2.0f, deltaTime / 0.1f);
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
		multiplySpeed = Camera::lerp(multiplySpeed, 0.5f, deltaTime / 0.1f);
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		multiplySpeed = Camera::lerp(multiplySpeed, 1.0f, deltaTime / 0.1f);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (!debounce) {
			glfwSetCursorPos(window, (width / 2), (height / 2));
			debounce = true;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newAngle = glm::rotate(angle, glm::radians(-rotX), glm::normalize(glm::cross(angle, upDirection)));

		if (abs(glm::angle(newAngle, upDirection) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			lerpAng = newAngle;
			angle = newAngle;
		}

		angle = glm::rotate(angle, glm::radians(-rotY), upDirection);

		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		debounce = false;
	}
}