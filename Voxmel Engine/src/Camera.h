#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	const float sensitivity = 0.08f;
	float moveSpeed = 5.0f;

	float pitch = 0, yaw = -90.0f, roll = 0;

	glm::vec3 transform = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraForward = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraSide = glm::vec3(1.0f, 0.0f, 0.0f);

	Camera(GLFWwindow* win, float* mousePos);

	void update(float delta);
private:
	GLFWwindow* window;
	float* mPos;

	float canFly = false;

	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
};
#endif // !CAMERA_H

