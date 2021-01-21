#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "WindowManager.h"
#include "Renderer.h"

#include "Entity.h"

#include <iostream>
#include <vector>

// Declarations
void processInput(GLFWwindow* window);

// Settings
const uint32_t WINDOW_WIDTH = 800;
const uint32_t WINDOW_HEIGHT = 600;

const char* windowTitle = "VoxMel Engine";

int main()
{
	WindowManager window(WINDOW_WIDTH, WINDOW_HEIGHT, windowTitle);
	Renderer renderer(window.get_window());

	Entity ent;
	renderer.addObj(ent);

	// Timesteps
	double limitFPS = 1.0 / 60.0, limitPhysicsSteps = 1.0 / 30.0;
	double lastTime = glfwGetTime(), nowTime = 0, timer = lastTime;
	double deltaTimeRender = 0, deltaTimePhysics = 0;
	uint32_t frames = 0, physicsUpdates = 0;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // For wireframe

	// Main Loop
	while (!glfwWindowShouldClose(window.get_window()))
	{
		// Timestep
		nowTime = glfwGetTime();
		deltaTimeRender += (nowTime - lastTime) / limitFPS;
		deltaTimePhysics += (nowTime - lastTime) / limitPhysicsSteps;
		lastTime = nowTime;

		// Reset the updates and fps counter every EARTH second
		if (glfwGetTime() - timer > 1.0)
		{
			timer++;
			std::string title = "VoxMel Engine | FPS : " + std::to_string(frames) + " | Physics : " + std::to_string(physicsUpdates);
			windowTitle = title.c_str();
			glfwSetWindowTitle(window.get_window(), windowTitle);
			//std::cout << "FPS: " << frames << " Physics Updates:" << physicsUpdates << std::endl;
			physicsUpdates = 0, frames = 0;
		}

		// Input
		processInput(window.get_window());

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

			// Draw Here

			renderer.render();

			// Check/Call events
			glfwPollEvents();
		}
	}

	// Release resources
	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteTextures(1, &texture);*/
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