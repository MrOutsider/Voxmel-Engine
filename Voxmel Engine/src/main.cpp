#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowManager.h"
#include "Renderer.h"

#include "Camera.h"
#include "Entity.h"

#include <iostream>
#include <vector>
#include <string>

// Declarations
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* win, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float delta = 0.0f;
float fps = 30.0f;

// Settings
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

std::string windowTitle = "VoxMel Engine";
const char* winTitle = windowTitle.c_str();

bool firstMouse = true;
float mousePos[4] = {
	WINDOW_WIDTH / 2,
	WINDOW_HEIGHT / 2,
	0.0f,
	0.0f };

float mouseScroll = 0.0f;

int main()
{
	WindowManager window(WINDOW_WIDTH, WINDOW_HEIGHT, winTitle);
	window.captureMouse();

	Renderer renderer(window.get_window(), &mouseScroll);

	// GLFW : Callback function
	glfwSetFramebufferSizeCallback(window.get_window(), framebuffer_size_callback);
	glfwSetCursorPosCallback(window.get_window(), mouse_callback);
	glfwSetScrollCallback(window.get_window(), scroll_callback);

	float* mouse_ptr = mousePos;
	Camera cam(window.get_window(), mouse_ptr);
	renderer.addCamera(cam);

	// Timesteps
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	fps = mode->refreshRate - 1.0f;
	float limitFPS = 1.0f / fps, limitPhysicsSteps = 1.0f / 30.0f;
	float lastTime = glfwGetTime(), nowTime = 0.0f, timer = lastTime;
	float deltaTimeRender = 0.0f, deltaTimePhysics = 0.0f;
	unsigned int frames = 0, physicsUpdates = 0;

	glfwMaximizeWindow(window.get_window());

	unsigned int ID = 0;

	Entity backPack(ID, "res/models/backpack.obj", "res/textures/diffuse.png");
	ID++;
	renderer.loadEntityBuffers(backPack);
	renderer.addEntity(backPack);

	// Main Loop
	while (!glfwWindowShouldClose(window.get_window()))
	{
		// Timestep
		nowTime = glfwGetTime();
		deltaTimeRender += (nowTime - lastTime) / limitFPS;
		deltaTimePhysics += (nowTime - lastTime) / limitPhysicsSteps;
		delta = nowTime - lastTime;
		lastTime = nowTime;

		// Reset the updates and fps counter every EARTH second
		if (glfwGetTime() - timer > 1.0)
		{
			timer++;
			std::string newTitle = windowTitle + " | FPS : " + std::to_string(frames) + " | Physics : " + std::to_string(physicsUpdates) + " | Draw : " + std::to_string(renderer.drawCalls);
			winTitle = newTitle.c_str();
			glfwSetWindowTitle(window.get_window(), winTitle);
			physicsUpdates = 0, frames = 0;
		}

		// Input
		processInput(window.get_window());
		cam.update(delta);

		if (deltaTimePhysics >= 1.0)
		{
			deltaTimePhysics--;
			physicsUpdates++;

			// Do physics here
		}

		if (deltaTimeRender >= 1.0)
		{
			deltaTimeRender--;
			frames++;

			glfwMakeContextCurrent(window.get_window());

			int w, h;
			glfwGetWindowSize(window.get_window(), &w, &h);

			glViewport(0, 0, w, h);

			renderer.render();

			glfwPollEvents();
		}
	}

	// Release resources
	renderer.destroy();

	glfwTerminate();
	return 0;
}

// This function is looped to detect input
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	// TAB
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

// GLFW: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* win, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		mousePos[2] = xpos;
		mousePos[3] = ypos;

		firstMouse = false;
	}
	float xoffset = xpos - mousePos[0];
	float yoffset = mousePos[1] - ypos; // Reversed since y-coordinates range from bottom to top
	mousePos[0] = xpos;
	mousePos[1] = ypos;
	mousePos[2] = xoffset;
	mousePos[3] = yoffset;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	mouseScroll = yoffset;
}

//for (unsigned int i = 0; i < 36; i++)
//{
//	chunkMesh.push_back(voxel[0 + (i * 5)] + (x * voxelSize * 2));
//	chunkMesh.push_back(voxel[1 + ((i * 1) * 5)] + (y * voxelSize * 2));
//	chunkMesh.push_back(voxel[2 + ((i * 1) * 5)] + (z * voxelSize * 2));
//	vertCount += 3;
//	chunkMesh.push_back(voxel[3 + ((i * 1) * 5)]);
//	chunkMesh.push_back(voxel[4 + ((i * 1) * 5)]);
//}
//
//if (!chunkMesh.empty())
//{
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, chunkMesh.size() * sizeof(float), &chunkMesh[0], GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	glBindVertexArray(0);
//}