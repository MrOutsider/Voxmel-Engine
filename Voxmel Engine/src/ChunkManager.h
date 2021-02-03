#ifndef CHUNK_MANAGER_H
#define CHUNK_MANAGER_H

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();

	void chunkSetterTest();
	void chunkMesher();

private:
	unsigned int chunkSize = 16;
	unsigned int chunk[4096] = {};
};

#endif // !CHUNK_MANAGER_H
