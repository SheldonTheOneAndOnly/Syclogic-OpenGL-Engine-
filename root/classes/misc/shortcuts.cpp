#include<classes/misc/shortcuts.h>
#include<stb_image.h>

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
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	int centerX = glfwGetVideoMode(glfwGetPrimaryMonitor())->width / 2 - windowWidth / 2;
	int centerY = glfwGetVideoMode(glfwGetPrimaryMonitor())->height / 2 - windowHeight / 2;

	ID = glfwCreateWindow(windowWidth, windowHeight, title, NULL, NULL);
	if (ID == NULL) {
		std::cout << "GLFW ERROR: Window failed to create" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(ID);

	gladLoadGL();

	glViewport(0, 0, windowWidth, windowHeight);

	glfwSetWindowUserPointer(ID, this);
	glfwSetWindowSizeCallback(ID, [](GLFWwindow* w, int wi, int he) {
		Window* i = static_cast<Window*>(glfwGetWindowUserPointer(w));

		if (i) {
			i->resize(wi, he);
		}
	});

	glfwSetWindowPos(ID, centerX, centerY);

	initialized = true;
	width = windowWidth;
	height = windowHeight;
}

bool Window::isValid() {
	if (initialized) { return true; }
	else { return false; };
}

void Window::Frame(string filename) {
}

void Window::Update() {
	curFrame = glfwGetTime();
	deltaTime = curFrame - lastFrame;
	lastFrame = curFrame;
	glfwSwapBuffers(ID);
	glfwPollEvents();

	if (glfwGetKey(this->ID, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		std::cout << "ESCAPE KEY PRESSED. SHUTTING DOWN..." << std::endl;
		glfwSetWindowShouldClose(this->ID, GL_TRUE);
	}
}

void Window::ChangeTitle(string title) {
	glfwSetWindowTitle(ID, title.c_str());
}

void Window::Destroy() {
	glfwDestroyWindow(ID);
}

static float SmoothStep(float x, float p1, float p2) {
	x = clamp((x - p1) / (p2 - p1), 0.0f, 1.0f);

	return x * x * (3.0f - 2.0f * x);
}