#include "Camera.h"

Camera::Camera(GLFWwindow* win, float* mousePos)
{
	window = win;
	mPos = mousePos;
}

void Camera::update(float delta)
{
	mPos[2] *= sensitivity;
	mPos[3] *= sensitivity;

	yaw += mPos[2];
	pitch += mPos[3];

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	cameraFront = glm::normalize(direction);
	cameraSide = glm::normalize(glm::cross(cameraFront, cameraUp));
	cameraForward = -glm::normalize(glm::cross(cameraSide, cameraUp));

	glm::vec3 newTransform = glm::vec3(0.0f, 0.0f, 0.0f);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (!canFly)
		{
			newTransform += cameraForward;
		}
		else
		{
			newTransform += cameraFront;
		}

	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (!canFly)
		{
			newTransform -= cameraForward;
		}
		else
		{
			newTransform -= cameraFront;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		newTransform -= cameraSide;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		newTransform += cameraSide;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		newTransform += cameraUp;
	}
	
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		newTransform -= cameraUp;
	}

	transform += newTransform * moveSpeed * delta;
}
