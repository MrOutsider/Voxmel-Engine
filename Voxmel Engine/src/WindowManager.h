#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class WindowManager
{
public:
	WindowManager(int width, int height, const char* windowTitle);

	GLFWwindow* get_window();
private:
	GLFWwindow* window;

	int init(int width, int height, const char* windowTitle);
};

#endif // !WINDOW_MANAGER_H
