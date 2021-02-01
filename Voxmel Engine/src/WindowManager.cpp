#include "WindowManager.h"

WindowManager::WindowManager(int width, int height, const char* windowTitle)
{
	init(width, height, windowTitle);
}

void WindowManager::captureMouse()
{
	// GLFW : Captures mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

int WindowManager::init(int width, int height, const char* windowTitle)
{
	// GLFW : Init and config window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// GLFW : Create window
	window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);
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
}

GLFWwindow* WindowManager::get_window()
{
	return window;
}
