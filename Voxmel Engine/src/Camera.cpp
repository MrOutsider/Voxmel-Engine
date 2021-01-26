#include "Camera.h"

Camera::Camera(GLFWwindow* win)
{
	window = win;
}

void Camera::move()
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		transform.z += 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		transform.z -= 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		transform.x += 0.01f;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		transform.x -= 0.01f;
	}
}
