#include<classes/rendering/Camera.h>

Camera::Camera(int Width, int Height, glm::vec3 Pos) {
	width = Width;
	height = Height;
	position = Pos;
	lerpPos = position;
}

void Camera::UpdateMat(int w, int h, float FOV, float nearZ, float farZ) {
	glm::mat4 v = glm::mat4(1.0f);
	glm::mat4 p = glm::mat4(1.0f);

	v = glm::lookAt(position, position + angle, upDirection);
	p = glm::perspective(glm::radians(FOV), (float)w / h, nearZ, farZ);

	view = v;
	projection = p;

	width = w;
	height = h;

	this->FOV = FOV;
	this->nearZ = nearZ;
	this->farZ = farZ;
}

void Camera::Mat(Shader& shader) {
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
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
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		lerpPos += (speed * multiplySpeed * upDirection) * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		lerpPos += (speed * multiplySpeed * -upDirection) * deltaTime;
	}

	position = vec3Lerp(position, lerpPos, deltaTime / 0.1f);

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		multiplySpeed = Camera::lerp(multiplySpeed, 2.0f, deltaTime / 0.1f);
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
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

		rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
		rotX = 0.0f;
		rotY = 0.0f;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		debounce = false;
	}

	lerpRot.x = lerp(lerpRot.x, rotX, deltaTime * 8.0f);
	lerpRot.y = lerp(lerpRot.y, rotY, deltaTime * 8.0f);

	glm::vec3 newAngle = glm::rotate(angle, glm::radians(-lerpRot.x), glm::normalize(glm::cross(angle, upDirection)));

	if (abs(glm::angle(newAngle, upDirection) - glm::radians(85.0f)) <= glm::radians(85.0f))
	{
		angle = newAngle;
	}

	angle = glm::rotate(angle, glm::radians(-lerpRot.y), upDirection);
}