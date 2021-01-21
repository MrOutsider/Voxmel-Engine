#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

class Entity
{
public:
	Entity();
	~Entity();

	// Getters
	std::vector<float>& getVertices();
	std::vector<uint32_t>& getIndices();
	std::vector<const char*>& getTextures();

private:
	std::vector<float> vertices;
	std::vector<uint32_t> indices;
	std::vector<const char*> textures;
};
#endif // !ENTITY_H

