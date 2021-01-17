#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class WindowManager
{
public:
	GLFWwindow* window;
	int init(int width, int height, const char* windowTitle);
private:
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif // !WINDOW_MANAGER_H
