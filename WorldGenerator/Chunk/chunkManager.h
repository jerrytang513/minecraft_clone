#ifndef CHUNKMANAGER_H_
#define CHUNKMANAGER_H_

#include "../Renderer/blockRenderer.h"
#include "../../src/Mesh/mesh.h"
#include "blockChunk.h"
#include <vector>

class ChunkManager{
  // Need 3 dimensional chunks
  std::vector<std::vector<std::vector<BlockChunk>>> chunks;
  BlockMesh mesh;
  int M_WIDTH;
  int M_HEIGHT = 16;
  int M_LENGTH;

  void initializeHeights();
public:
  ChunkManager(int width, int length);
  ChunkManager(int width, int length, std::vector<int> heights);
  void draw(BlockRenderer renderer);
  void addHeight(std::vector<int> heights);
  std::vector<std::vector<std::vector<BlockChunk>>>& getChunks();
  void addFace();
};

#endif
