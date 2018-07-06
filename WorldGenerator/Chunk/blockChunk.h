#ifndef BLOCKCHUNK_H_
#define BLOCKCHUNK_H_

#include "../blockInfo.h"
#include "../../Vec3D.h"
#include "../Renderer/blockRenderer.h"
#include "../../shader.h"
#include "direction.h"
#include <vector>

class BlockChunk{

// Manage Textures
// Manage Blocks
  std::vector<std::vector<std::vector<BlockInfo>>> blocks;
  int initWidth;
  int initLength;
  int initHeight;
  std::vector<BlockInfo> displayList;
  bool needUpdate = true;


public:
  BlockChunk();
  // Feed in Block Chunk size of height data, and block chunk will build the coords
  BlockChunk(int width, int height, int length, std::vector<int> heights);

  void setConfig(int width, int height, int length);

  std::vector<std::vector<std::vector<BlockInfo>>> getBlockInfo();
  void addHeight(int width, int height, int length);
  void updateDisplayList();
  void draw(BlockRenderer renderer);
  void setUpdate(bool status);
  void addFace(int i, int j, int k, Direction direction);
};
#endif
