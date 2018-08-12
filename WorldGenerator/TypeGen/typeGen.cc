#include "typeGen.h"

TypeGen::TypeGen():waterLevel{70}, sandLevel{4}, rockLevel{8}, snowLevel{100}{}

TypeGen& TypeGen::getInstance(){
  static TypeGen tg;
  return tg;
}

void TypeGen::genType(int curMinHeight, std::vector<std::vector<std::vector<BlockInfo>>>& blocks, std::vector<int>& highest){

  for(int length = 0; length < 16; ++length){
    for(int width = 0; width < 16; ++width){
      int curMaxHeight = highest[length * 16 + width];

      for(int height = 0; height < 16; ++height){
        int curHeight = curMinHeight + height;
        blocks[width][height][length].visible = true;
        // if the max height is above waterlevel and below sandLevel amount, then
        //    there will be 4 levels of sand blocks underneath the max height block which is from maxHeight - 5 to maxHeight - 1, since index start from 0

        // if the max height is above waterLevel and above sandLevel amount, then
        //    if the current Height is at maxHeight - 1, then it will become a grass block
        //    if the current Height is below maxHeight - 1, and it is above maxHeight - 1 - rockLevel, then it will be a dirt block
        //    if the current Height is below maxHeight - 1 - rockLevel, then it become a rock block

        // If the max height is below waterLevel, then
        //    if the current Height is at maxHeight to waterlevel, then it will be a water block
        //    if the current Height is below maxheight - rockLevel - 1, it will be a rock block
        //    if the current height is at maxHeight - rockLevel -1 to maxHeight - 1, it will be a sand block
        if(curMaxHeight > waterLevel + sandLevel){
            if(curHeight == curMaxHeight - 1){
              blocks[width][height][length].type = BLOCKTYPE::GRASS;
            } else if(curHeight > curMaxHeight - 1 - rockLevel && curHeight < curMaxHeight - 1){
              blocks[width][height][length].type = BLOCKTYPE::DIRT;
            } else if(curHeight <= curMaxHeight - 1 - rockLevel){
              blocks[width][height][length].type = BLOCKTYPE::ROCK;
            }
        } else if (curMaxHeight > waterLevel) {
            if(curHeight > curMaxHeight - 1 - sandLevel && curHeight < curMaxHeight){
              blocks[width][height][length].type = BLOCKTYPE::SAND;
            } else if(curHeight <= curMaxHeight - 1 - sandLevel){
              blocks[width][height][length].type = BLOCKTYPE::ROCK;
            }
        } else {
            if(curHeight >= curMaxHeight && curHeight < waterLevel){
              blocks[width][height][length].type = BLOCKTYPE::WATER;
            } else if(curHeight > curMaxHeight - sandLevel && curHeight < curMaxHeight){
              blocks[width][height][length].type = BLOCKTYPE::SAND;
            } else if(curHeight <= curMaxHeight - sandLevel){
              blocks[width][height][length].type = BLOCKTYPE::ROCK;
            }
        }

        if(blocks[width][height][length].type == BLOCKTYPE::AIR){
          blocks[width][height][length].visible = false;
        }

      }

    }
  }

}

int TypeGen::getMinHeight(){
  return waterLevel + sandLevel;
}
