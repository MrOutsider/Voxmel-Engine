#ifndef CHUNCK_MANAGER_H
#define CHUNCK_MANAGER_H

#include <vector>

#define AIR		0
#define STONE	1
#define DIRT	2

class ChunkManager
{
public:
	ChunkManager();

private:
	int chunk[4096];

	std::vector<float> chunkMesh;
};

#endif // !CHUNCK_MANAGER_H

