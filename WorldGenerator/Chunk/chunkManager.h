#ifndef CHUNKMANAGER_H_
#define CHUNKMANAGER_H_

#include <vector>
#include <memory>

#include "blockChunk.h"
#include "heightChunk.h"
#include "../Renderer/chunkRenderer.h"
#include "../../src/Mesh/mesh.h"
#include "../../src/utility/threadPool.h"
#include "../../vec3d.h"

class ChunkManager{
  // Need 3 dimensional chunks
  std::vector<std::vector<std::vector<BlockChunk>>> m_chunks;
  std::vector<std::vector<std::shared_ptr<HeightChunk>>> m_heightChunks;

  std::vector<Vec3D> renderList;
  int M_WIDTH;
  int M_HEIGHT;
  int M_LENGTH;

  int centerX;
  int centerY;

  void initializeHeights();
  bool shouldAddFace(int chunkX, int chunkY, int chunkZ);

public:
  ChunkManager(int width, int length);
  ChunkManager(int width, int length, std::vector<int> heights);
  void draw(ChunkRenderer renderer);
  void addHeight(std::vector<int> heights);
  const std::vector<std::vector<std::vector<BlockChunk>>> getChunks();
  void initMesh();
  void generateChunkMesh(int chunkX, int chunkY, int chunkZ);
};
#endif
