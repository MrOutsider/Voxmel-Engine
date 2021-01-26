#include "Camera.h"

Camera::Camera(GLFWwindow* win)
{
	window = win;
}

void Camera::move(float delta)
{
	float speed = 5.0f;

	glm::vec3 newTransform = glm::vec3(0.0f, 0.0f, 0.0f);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		newTransform.z += 1.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		newTransform.z -= 1.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		newTransform.x += 1.0f;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		newTransform.x -= 1.0f;
	}

	transform += newTransform * speed * delta;
}
