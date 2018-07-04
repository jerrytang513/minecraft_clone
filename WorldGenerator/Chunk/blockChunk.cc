#include "blockChunk.h"//TODO
BlockChunk::BlockChunk():blocks{std::vector<std::vector<std::vector<BlockInfo>>>(16, std::vector<std::vector<BlockInfo>>(16,std::vector<BlockInfo>(16,BlockInfo())))}{}
BlockChunk::BlockChunk(int width,  int height, int length, std::vector<int> heights):initWidth{width},initHeight{height},initLength{length},blocks{std::vector<std::vector<std::vector<BlockInfo>>>(16, std::vector<std::vector<BlockInfo>>(16,std::vector<BlockInfo>(16,BlockInfo())))}{



}

std::vector<std::vector<std::vector<BlockInfo>>> BlockChunk::getBlockInfo(){
  return blocks;
}

void BlockChunk::addHeight(int width, int height, int length){
  if(height > 16)
    height = 16;
  for(int i = 0; i < height; i++){
    BlockInfo block;
    block.x = width + initWidth;
    block.y = i + initHeight;
    block.z = length + initLength;
    block.visible = true;
    blocks[width][i][length] = block;
  }

  std:: cout << "SUCCESS" << std::endl;
}

void BlockChunk::setConfig(int width, int height, int length){
  initWidth = width;
  initHeight = height;
  initLength = length;
}

void BlockChunk::setUpdate(bool status){
  needUpdate = status;
}

void BlockChunk::updateDisplayList(){
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      for(int k = 0; k < 16; k++){
        std::cout << blocks[i][k][j].visible << std::endl;
        if(blocks[i][k][j].visible == true && (i == 0 || i == 15 || j == 0 || j == 15 || k == 0 || k == 15)){
          displayList.emplace_back(blocks[i][k][j]);
        } else if (blocks[i][k][j].visible == true &&
                !(blocks[i-1][k][j].visible == true &&
                  blocks[i+1][k][j].visible == true &&
                  blocks[i][k-1][j].visible == true &&
                  blocks[i][k+1][j].visible == true &&
                  blocks[i][k][j-1].visible == true &&
                  blocks[i][k][j+1].visible == true)){
          displayList.emplace_back(blocks[i][k][j]);
        }
      }
    }
  }
}

void BlockChunk::draw(BlockRenderer renderer){
  if(needUpdate){
    displayList.clear();
    updateDisplayList();
    needUpdate = false;
  }
  Shader shader = renderer.getShader();
  renderer.draw(displayList);


}
