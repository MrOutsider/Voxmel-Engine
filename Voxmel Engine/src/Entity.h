#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

class Entity
{
public:
	unsigned int ID;

	const char* modelPath;
	const char* albedoPath;

	glm::vec3 transform = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	Entity(unsigned int newID, const char* newModelPath, const char* newAlbedoPath);
};
#endif // !ENTITY_H

