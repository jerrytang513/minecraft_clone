#ifndef WORLDGENERATOR_BLOCKTEXTURES_H_
#define WORLDGENERATOR_BLOCKTEXTURES_H_

#include <mutex>
#include <vector>

#include "../blockInfo.h"
#include "../Resource/textureManager.h"

#include "../../vec2d.h"

struct BlockSideCoords {
	std::vector<Vec2D> top;
	std::vector<Vec2D> side;
	std::vector<Vec2D> bottom;
	BlockSideCoords(std::vector<Vec2D> top, std::vector<Vec2D> side, std::vector<Vec2D> bottom) :top{ top }, side{ side }, bottom{ bottom } {}
	BlockSideCoords() {}
};

class BlockTextures{


  BlockTextures();
  static void init();

  static std::vector<BlockSideCoords> blockSideCoords;
  static std::once_flag initInstanceFlag;

public:

  static BlockTextures& getInstance();
  BlockSideCoords& getTextureCoordinatesByType(BLOCKTYPE type);


};

#endif
