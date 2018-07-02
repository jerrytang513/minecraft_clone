#ifndef BLOCKCHUNK_H_
#define BLOCKCHUNK_H_

#include "../coordinate.h"
#include <vector>

class BlockChunk{

// Manage Textures
// Manage Blocks
  std::vector<Coordinate> coords(16 * 16 * 16, 0);

public:
  BlockChunk();
  // Feed in Block Chunk size of height data, and block chunk will build the coords
  BlockChunk(std::vector<std::vector<int>> heights);

  std::vector<Coordinate> getCoords();


};
#endif
