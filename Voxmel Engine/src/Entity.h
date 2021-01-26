#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include <vector>

struct Texture
{
	const char* albedo = "NULL";
	const char* secondTexture = "NULL";
};

struct ModelData
{
	std::vector<float> vertices;
	std::vector<uint32_t> indices;
	Texture texture;
};

class Entity
{
public:
	ModelData modelData;
	glm::vec3 transform = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 rotation = glm::vec3(25.0f, 50.0f, 0.0f);

	Entity();
	~Entity();
};
#endif // !ENTITY_H

