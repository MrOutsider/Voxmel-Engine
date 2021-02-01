#include "WindowManager.h"

// GLFW: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* win, int width, int height)
{
	glViewport(0, 0, width, height);
}

WindowManager::WindowManager(int width, int height, const char* windowTitle)
{
	init(width, height, windowTitle);
}

int WindowManager::init(int width, int height, const char* windowTitle)
{
	// GLFW : Init and config window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, NULL);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// GLFW : Create window
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	float window_width = mode->width;
	float window_height = mode->height;

	window = glfwCreateWindow(window_width, window_height, windowTitle, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD." << std::endl;
		return -1;
	}

	// GLFW : Captures mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// GLFW : Callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

GLFWwindow* WindowManager::get_window()
{
	return window;
}
