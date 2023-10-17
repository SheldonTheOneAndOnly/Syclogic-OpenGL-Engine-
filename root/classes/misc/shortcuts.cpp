#include<classes/misc/shortcuts.h>

Window::Window(int windowWidth, int windowHeight, const char* title, unsigned int samples) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_SAMPLES, samples);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	ID = glfwCreateWindow(windowWidth, windowHeight, title, NULL, NULL);
	if (ID == NULL) {
		std::cout << "Hey fuckwad, the window you tried to create failed to render." << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(ID);

	gladLoadGL();

	glViewport(0, 0, windowWidth, windowHeight);

	initialized = true;
	width = windowWidth;
	height = windowHeight;
}

bool Window::isValid() {
	if (initialized) { return true; } else { return false; };
}

void Window::Update() {
	glfwSwapBuffers(ID);
	glfwPollEvents();
}

void Window::Destroy() {
	glfwDestroyWindow(ID);
}