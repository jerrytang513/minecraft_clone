#ifndef CHUNKMANAGER_H_
#define CHUNKMANAGER_H_

#include "../Renderer/blockRenderer.h"
#include "../../src/Mesh/mesh.h"
#include "blockChunk.h"
#include <vector>

class ChunkManager{
  // Need 3 dimensional chunks
  std::vector<std::vector<std::vector<BlockChunk>>> m_chunks;
  int M_WIDTH;
  int M_HEIGHT = 16;
  int M_LENGTH;

  void initializeHeights();
  bool shouldAddFace();

public:
  ChunkManager(int width, int length);
  ChunkManager(int width, int length, std::vector<int> heights);
  void draw(BlockRenderer renderer);
  void addHeight(std::vector<int> heights);
  const std::vector<std::vector<std::vector<BlockChunk>>>& getChunks();
  void initMesh();
  void generateChunkMesh(int chunkX, int chunkY, int chunkZ);};

#endif
