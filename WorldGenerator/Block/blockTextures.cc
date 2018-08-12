#include "blockTextures.h"

BlockTextures::BlockTextures(){}

void BlockTextures::init(){
  TextureManager& tm = TextureManager::getInstance();

  // GRASS
  blockSideCoords.emplace_back(
    BlockSideCoords(
      tm.getCoordinates(Vec2D(0,15)),
      tm.getCoordinates(Vec2D(3,15)),
      tm.getCoordinates(Vec2D(2,15))
    )
  );
  // SAND
  blockSideCoords.emplace_back(
    BlockSideCoords(
      tm.getCoordinates(Vec2D(14,7)),
      tm.getCoordinates(Vec2D(14,7)),
      tm.getCoordinates(Vec2D(14,7))
    )
  );
  // DIRT
  blockSideCoords.emplace_back(
    BlockSideCoords(
      tm.getCoordinates(Vec2D(2,15)),
      tm.getCoordinates(Vec2D(2,15)),
      tm.getCoordinates(Vec2D(2,15))
    )
  );
  // ROCK
  blockSideCoords.emplace_back(
    BlockSideCoords(
      tm.getCoordinates(Vec2D(1,15)),
      tm.getCoordinates(Vec2D(1,15)),
      tm.getCoordinates(Vec2D(1,15))
    )
  );
  // WATER
  blockSideCoords.emplace_back(
    BlockSideCoords(
      tm.getCoordinates(Vec2D(14,2)),
      tm.getCoordinates(Vec2D(14,2)),
      tm.getCoordinates(Vec2D(14,2))
    )
  );
}

BlockTextures& BlockTextures::getInstance(){
  static BlockTextures bt;
  std::call_once(initInstanceFlag, &BlockTextures::init);
  return bt;
}

BlockSideCoords& BlockTextures::getTextureCoordinatesByType(BLOCKTYPE type){
    switch(type){
      case BLOCKTYPE::GRASS:
        return blockSideCoords[0];
      case BLOCKTYPE::SAND:
        return blockSideCoords[1];
      case BLOCKTYPE::DIRT:
        return blockSideCoords[2];
      case BLOCKTYPE::ROCK:
        return blockSideCoords[3];
      default:
        // This should be water
        return blockSideCoords[4];
	};
}

std::vector<BlockSideCoords> BlockTextures::blockSideCoords;
std::once_flag BlockTextures::initInstanceFlag;
