#ifndef ENTITY_H
#define ENTITY_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "PhysicsManager.h"

#include <vector>

class Entity
{
public:
	unsigned int ID;

	const char* modelPath;
	const char* albedoPath;

	// OpenGL : Buffers
	// TODO : Load all models at start and ref them from Entity Class
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	std::vector<unsigned int> indices;

	// OpenGL : Textures
	GLuint albedo;

	AABB collisionBox;

	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	Entity(unsigned int newID, const char* newModelPath, const char* newAlbedoPath);
};
#endif // !ENTITY_H
