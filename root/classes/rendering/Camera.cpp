#include<classes/rendering/Camera.h>

Camera::Camera(int Width, int Height, glm::vec3 Pos) {
	width = Width;
	height = Height;
	position = Pos;
}

void Camera::UpdateMat(float FOV, float nearZ, float farZ) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(position, position + angle, upDirection);
	projection = glm::perspective(glm::radians(FOV), (float)(width / height), nearZ, farZ);

	camMat = projection * view;
}

void Camera::Mat(Shader& shader, const char* uni) {
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uni), 1, GL_FALSE, glm::value_ptr(camMat));

}

void Camera::Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += speed / 50 * angle;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position += speed / 50 * -angle;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position += speed / 50 * -glm::normalize(glm::cross(angle, upDirection));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += speed / 50 * glm::normalize(glm::cross(angle, upDirection));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		position += speed / 50 * upDirection;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		position += speed / 50 * -upDirection;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed = 0.025f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = 0.125f;
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