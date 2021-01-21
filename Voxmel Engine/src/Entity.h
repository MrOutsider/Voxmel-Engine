#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

struct ModelData
{
	std::vector<float> vertices;
	std::vector<uint32_t> indices;
	const char* texture;
};

struct Transform
{
	double x = 0;
	double y = 0;
	double z = 0;
};

struct Scale
{
	double x = 0;
	double y = 0;
	double z = 0;
};

class Entity
{
public:
	Entity();
	~Entity();

	// Getters
	ModelData& getModelData();

private:
	ModelData modelData;
	Transform transform;
	Scale scale;
};
#endif // !ENTITY_H

