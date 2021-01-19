#include "Renderer.h"

void Renderer::init(GLFWwindow* win)
{
	window = win;
	compileShaders();
}


void Renderer::compileShaders()
{
	Shader newShader;
	shaders.push_back(newShader);
	shaders.back().create("res/shaders/basic.vs", "res/shaders/basic.fs");
}

void Renderer::loadTextures()
{
}

void Renderer::loadModels()
{
}

void Renderer::render()
{
	shaders[0].use();
}

void Renderer::destroy()
{
	shaders[0].destroy();
}
