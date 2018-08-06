#ifndef WORLDSPACE_H_
#define WORLDSPACE_H_
#include <utility>
#include <vector>
#include <cstdlib>
#include <mutex>

#include "../cube.h"
#include <GL/glew.h>
#include "perlinNoise.h"
#include "../src/Mesh/blockMesh.h"
#include "NoiseGen/noiseGen.h"
#include "../shader.h"
#include "Renderer/blockRenderer.h"
#include "Renderer/chunkRenderer.h"
#include "Chunk/chunkManager.h"
#include "Chunk/blockChunk.h"
#include "blockInfo.h"

#include "../src/utility/threadPool.h"

// This class manages the blocks inside the world
class WorldSpace{
  ChunkManager* chunkManager;
  ChunkRenderer chunkRenderer;

  PerlinNoise pn;
  int seed;
  int centerX = 100000;
  int centerY = 100000;

  std::recursive_mutex  movementMutex;

public:
  WorldSpace(int width, int length, int height);
  void draw(Shader shader);

// The front back left right location is constant inside the world space
// Consider front and back to be moving along the length axis (z - axis)
// Consider left and right to be moving along the width axis (x - axis)
  void moveFront();
  void moveBack();
  void moveLeft();
  void moveRight();

  void moveFront(int num);
  void moveBack(int num);
  void moveLeft(int num);
  void moveRight(int num);

  void click();

};

#endif
