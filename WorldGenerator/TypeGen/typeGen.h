#ifndef WORLDGENERATOR_TYPEGEN_TYPEGEN_
#define WORLDGENERATOR_TYPEGEN_TYPEGEN_

#include <iostream>
#include <mutex>
#include <vector>
#include <memory>

#include "../blockInfo.h"
#include "../Chunk/blockChunk.h"

class TypeGen{

  TypeGen();
  int waterLevel;
  int sandLevel;
  int rockLevel;
  int snowLevel;

public:

  static TypeGen& getInstance();

  void genType(int startHeight, std::vector<std::vector<std::vector<BlockInfo>>>& blocks, std::vector<int>& highest);
  int getMinHeight();

};

#endif
