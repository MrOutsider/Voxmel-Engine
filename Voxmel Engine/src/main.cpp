#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "WindowManager.h"
#include "Renderer.h"

#include "Camera.h"
#include "Entity.h"

#include <iostream>
#include <vector>
#include <string>

// Declarations
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float delta = 0.0f;

// Settings
const uint32_t WINDOW_WIDTH = 800;
const uint32_t WINDOW_HEIGHT = 600;

std::string windowTitle = "VoxMel Engine";
const char* winTitle = windowTitle.c_str();

bool firstMouse = true;
glm::vec4 mousePos = glm::vec4(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0.0f, 0.0f);
float mouseScroll = 0.0f;

int main()
{
	WindowManager window(WINDOW_WIDTH, WINDOW_HEIGHT, winTitle);
	Renderer renderer(window.get_window(), &mouseScroll);

	glfwSetCursorPosCallback(window.get_window(), mouse_callback);
	glfwSetScrollCallback(window.get_window(), scroll_callback);

	Camera cam(window.get_window(), &mousePos);
	renderer.addCamera(cam);

	for (uint32_t i = 0; i < 10; i++)
	{
		Entity newE;
		renderer.addEntityRenderTarget(newE);
	}

	// Timesteps
	float limitFPS = 1.0 / 60.0, limitPhysicsSteps = 1.0 / 30.0;
	float lastTime = glfwGetTime(), nowTime = 0, timer = lastTime;
	float deltaTimeRender = 0, deltaTimePhysics = 0;
	uint32_t frames = 0, physicsUpdates = 0;

	glEnable(GL_DEPTH_TEST); // May be moved
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // For wireframe

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
			std::string newTitle = windowTitle + " | FPS : " + std::to_string(frames) + " | Physics : " + std::to_string(physicsUpdates);
			winTitle = newTitle.c_str();
			glfwSetWindowTitle(window.get_window(), winTitle);
			//std::cout << "FPS: " << frames << " Physics Updates:" << physicsUpdates << std::endl;
			physicsUpdates = 0, frames = 0;
		}

		// Input
		processInput(window.get_window());

		cam.move(delta);

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

			// Do Update() stuff before rendering

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
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		mousePos.z = xpos;
		mousePos.w = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - mousePos.x;
	float yoffset = mousePos.y - ypos; // Reversed since y-coordinates range from bottom to top
	mousePos.x = xpos;
	mousePos.y = ypos;
	mousePos.z = xoffset;
	mousePos.w = yoffset;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	mouseScroll = yoffset;
}
