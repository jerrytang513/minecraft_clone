#ifndef WORLDGENERATOR_BLOCKTEXTURES_H_
#define WORLDGENERATOR_BLOCKTEXTURES_H_

#include "../blockInfo.h"
#include <mutex>

class BlockTextures{

  BlockTextures();
  static void init();

  static std::once_flag initInstanceFlag;

public:

  static BlockTextures& getInstance();


};

#endif
