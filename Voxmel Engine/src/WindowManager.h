#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class WindowManager
{
public:
	int init(int width, int height, const char* windowTitle);
	GLFWwindow* get_window();
private:
	GLFWwindow* window;
};

#endif // !WINDOW_MANAGER_H
