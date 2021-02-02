#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include <vector>

class Entity
{
public:
	glm::vec3 transform = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 rotation = glm::vec3(25.0f, 50.0f, 0.0f);

	Entity();
	~Entity();
};
#endif // !ENTITY_H

