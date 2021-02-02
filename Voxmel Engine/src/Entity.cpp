#include "Entity.h"

Entity::Entity(unsigned int newID, const char* newModelPath, const char* newAlbedoPath)
{
	ID = newID;
	modelPath = newModelPath;
	albedoPath = newAlbedoPath;
}
