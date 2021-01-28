#include "Camera.h"

Camera::Camera(GLFWwindow* win, glm::vec4* mousePos)
{
	window = win;
	mPos = mousePos;
}

void Camera::update(float& delta)
{
	std::cout << delta << std::endl;

	mPos->z *= sensitivity;
	mPos->w *= sensitivity;

	yaw += mPos->z;
	pitch += mPos->w;

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
		newTransform -= glm::normalize(glm::cross(cameraFront, cameraUp));
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		newTransform += glm::normalize(glm::cross(cameraFront, cameraUp));
	}

	transform += newTransform * moveSpeed * delta;
}
