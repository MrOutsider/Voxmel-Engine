#include "Renderer.h"

Renderer::Renderer(GLFWwindow* win)
{
	window = win;
}

void Renderer::tutSetUp()
{
	Renderer::shaders.push_back(Shader("res/shaders/basic.vs", "res/shaders/basic.fs"));
}

void Renderer::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	Renderer::shaders[0].use();
}
