#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

struct Texture
{
	const char* albedo = "NULL";
};

struct ModelData
{
	std::vector<float> vertices;
	std::vector<uint32_t> indices;
	Texture texture;
};

struct Transform
{
	double x = 0;
	double y = 0;
	double z = 0;
};

struct LocalTransform
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

	ModelData modelData;
	Transform transform;
	LocalTransform localTransform;
	Scale scale;

private:
	
};
#endif // !ENTITY_H

