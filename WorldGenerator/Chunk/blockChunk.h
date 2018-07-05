#ifndef BLOCKCHUNK_H_
#define BLOCKCHUNK_H_

#include "../blockInfo.h"
#include "../Renderer/blockRenderer.h"
#include "../../shader.h"
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

  //TODO Add chunk Mesh function
};
#endif
