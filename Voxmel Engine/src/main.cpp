#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowManager.h"
#include "Shader.h"

#include <iostream>

// Declarations
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Settings
const uint32_t WINDOW_WIDTH = 800;
const uint32_t WINDOW_HEIGHT = 600;

int main()
{
	WindowManager window;
	window.init(WINDOW_WIDTH, WINDOW_HEIGHT, "VoxMel Engine");

	//// GLFW : Init and setup the viewport change callback
	glfwSetFramebufferSizeCallback(window.get_window(), framebuffer_size_callback);

	Shader basicShader("res/shaders/basic.vs", "res/shaders/basic.fs");

	float vertices[] = {
	// Verts				UV
	-0.5f,  0.5f, 0.0f,		0.0, 1.0,
	 0.5f,  0.5f, 0.0f,		1.0, 1.0,
	 0.5f, -0.5f, 0.0f,		1.0, 0.0,
	-0.5f, -0.5f, 0.0f,		0.0, 0.0
	};
	uint32_t indices[] = {  // note that we start from 0!
		0, 1, 3,
		1, 2, 3
	};

	// Gen and asaign these var IDs
	uint32_t VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// Copy vertices array into a Vertex Buffer Object for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Copy indices array into an Element Array Buffer Object for OpenGL to reuse verts from the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); // Unbind the VAO so it is not changed further

	// Timesteps
	double limitFPS = 1.0 / 60.0, limitPhysicsSteps = 1.0 / 30.0;
	double lastTime = glfwGetTime(), nowTime = 0, timer = lastTime;
	double deltaTimeRender = 0, deltaTimePhysics = 0;
	int frames = 0, physicsUpdates = 0;

	// Main Loop
	while (!glfwWindowShouldClose(window.get_window()))
	{
		// Timestep
		nowTime = glfwGetTime();
		deltaTimeRender += (nowTime - lastTime) / limitFPS;
		deltaTimePhysics += (nowTime - lastTime) / limitPhysicsSteps;
		lastTime = nowTime;

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
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			basicShader.use();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// Check/Call events and swap buffers
			glfwSwapBuffers(window.get_window());
			glfwPollEvents();
		}

		// Reset the updates and fps counter every EARTH second
		if (glfwGetTime() - timer > 1.0)
		{
			timer++;
			//std::cout << "FPS: " << frames << " Physics Updates:" << physicsUpdates << std::endl;
			physicsUpdates = 0, frames = 0;
		}
	}

	// Release resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	basicShader.destroy();

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

// GLFW: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}