#include "blockTextures.h"

BlockTextures::BlockTextures(){}

void BlockTextures::init(){

}

BlockTextures& BlockTextures::getInstance(){
  static BlockTextures bt;
  std::call_once(initInstanceFlag, &BlockTextures::init);
  return bt;
}

std::once_flag BlockTextures::initInstanceFlag;
