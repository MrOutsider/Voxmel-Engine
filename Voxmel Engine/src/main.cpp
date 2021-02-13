#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowManager.h"
#include "ChunkManager.h"
#include "PhysicsManager.h"
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

	float* mouse_ptr = mousePos;
	Camera camera(window.get_window(), mouse_ptr);

	PhysicsManager physicsManager;

	ChunkManager chunkManager(physicsManager);
	chunkManager.init();
	
	// EntityManager(ChunkManager, PhysicsManager, Camera player)

	Renderer renderer(window.get_window(), &mouseScroll, chunkManager, physicsManager);
	renderer.addCamera(camera);
	bool cameraSet = false;

	glfwMaximizeWindow(window.get_window());

	// GLFW : Callback function
	glfwSetFramebufferSizeCallback(window.get_window(), framebuffer_size_callback);
	glfwSetCursorPosCallback(window.get_window(), mouse_callback);
	glfwSetScrollCallback(window.get_window(), scroll_callback);

	// Timesteps
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	fps = mode->refreshRate;
	float physcsSteps = 30.0f;
	float limitFPS = 1.0f / fps, limitPhysicsSteps = 1.0f / physcsSteps;
	float lastTime = glfwGetTime(), nowTime = 0.0f, timer = lastTime;
	float deltaTimeRender = 0.0f, deltaTimePhysics = 0.0f;
	unsigned int frames = 0, physicsUpdates = 0;

	// TMP
	Entity monkey(0, "res/models/monk.obj", "res/textures/container2.png");
	monkey.collisionBox.ID = physicsManager.assignID();
	monkey.collisionBox.typeOfBody = monkey.collisionBox.KINEMATIC;
	monkey.collisionBox.position.x = 16 + 8;
	monkey.collisionBox.position.y = 33;
	monkey.collisionBox.position.z = 16 + 8;

	monkey.collisionBox.xLength = 0.9f;
	monkey.collisionBox.zLength = 0.9f;
	monkey.collisionBox.yLength = 1.9f;

	monkey.scale = glm::vec3(1.5f, 4.0f, 2.0f);

	physicsManager.dynamicList.push_back(&monkey.collisionBox);
	renderer.addEntity(monkey);
	renderer.loadEntityBuffers(monkey);

	Raycast ray1;
	ray1.ID = physicsManager.assignID();
	ray1.length = 2;
	ray1.Direction = glm::vec3(1.0f, 0.0f, 0.0f);
	physicsManager.addRaycast(ray1);

	Raycast cameraRay;
	cameraRay.ID = physicsManager.assignID();
	cameraRay.visable = false;
	cameraRay.length = 10;
	physicsManager.addRaycast(cameraRay);

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

		if (!cameraSet)
		{
			camera.transform = glm::vec3(-30.0f, 30.0f, -15.0f);
			cameraSet = true;
		}

		camera.update(delta);
		cameraRay.position = camera.transform;
		cameraRay.Direction = camera.cameraFront;

		ray1.position = monkey.collisionBox.position;

		// TMP
		if (glfwGetKey(window.get_window(), GLFW_KEY_UP) == GLFW_PRESS)
		{
			monkey.collisionBox.position.y += 5 * delta;
		}
		if (glfwGetKey(window.get_window(), GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			monkey.collisionBox.position.y -= 5 * delta;
		}
		if (glfwGetKey(window.get_window(), GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			monkey.collisionBox.position.z -= 5 * delta;
		}
		if (glfwGetKey(window.get_window(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			monkey.collisionBox.position.z += 5 * delta;
		}
		if (glfwGetKey(window.get_window(), GLFW_KEY_COMMA) == GLFW_PRESS)
		{
			monkey.collisionBox.position.x += 5 * delta;
		}
		if (glfwGetKey(window.get_window(), GLFW_KEY_PERIOD) == GLFW_PRESS)
		{
			monkey.collisionBox.position.x -= 5 * delta;
		}

		if (deltaTimePhysics >= 1.0)
		{
			deltaTimePhysics--;
			physicsUpdates++;

			physicsManager.update(delta);
		}

		if (deltaTimeRender >= 1.0)
		{
			deltaTimeRender--;
			frames++;

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

// GLFW : Whenever the window size changed (by OS or user resize) this callback function executes
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