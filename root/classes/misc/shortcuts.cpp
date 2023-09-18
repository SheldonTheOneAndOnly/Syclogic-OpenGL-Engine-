#include<classes/misc/shortcuts.h>

Window::Window(int width, int height, const char* title) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	ID = glfwCreateWindow(width, height, title, NULL, NULL);
	if (ID == NULL) {
		std::cout << "Hey fuckwad, the window you tried to create failed to render." << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(ID);

	gladLoadGL();

	glViewport(0, 0, 800, 600);

	initialized = true;
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