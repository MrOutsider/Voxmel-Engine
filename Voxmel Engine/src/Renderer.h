#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Shader.h"

class Renderer
{
public:
	Renderer(GLFWwindow* win);
	void tutSetUp();
	void render();
private:
	GLFWwindow* window;
	std::vector<Shader> shaders;
};

#endif // !RENDERER_H

