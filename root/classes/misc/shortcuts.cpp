#include<classes/misc/shortcuts.h>
#include<stb/stb_image.h>

std::string GetFileContents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

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
	if (initialized) { return true; }
	else { return false; };
}

void Window::Update() {
	curFrame = glfwGetTime();
	deltaTime = curFrame - lastFrame;
	lastFrame = curFrame;
	glfwSwapBuffers(ID);
	glfwPollEvents();
}

void Window::Destroy() {
	glfwDestroyWindow(ID);
}