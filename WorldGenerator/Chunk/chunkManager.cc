#include "chunkManager.h"


ChunkManager::ChunkManager(int width, int length):M_WIDTH{width},M_LENGTH{length},chunks{std::vector<std::vector<std::vector<BlockChunk>>>(2, std::vector<std::vector<BlockChunk>>(2,std::vector<BlockChunk>(2,BlockChunk())))}{
}
ChunkManager::ChunkManager(int width, int length,std::vector<int> heights):M_WIDTH{width},M_LENGTH{length}{

  std::vector<std::vector<std::vector<BlockChunk>>> temp {std::vector<std::vector<std::vector<BlockChunk>>>(M_WIDTH, std::vector<std::vector<BlockChunk>>(M_HEIGHT,std::vector<BlockChunk>(M_LENGTH,BlockChunk())))};
  chunks = temp;
  initializeHeights();
  addHeight(heights);
  std::cout << M_WIDTH << "  " << M_LENGTH << std::endl;
}

void ChunkManager::initializeHeights(){
  for(int i = 0; i < M_WIDTH; i++){
    for(int j = 0; j < M_LENGTH; j++){
      for(int k = 0; k < M_HEIGHT; k++){

        chunks[i][k][j].setConfig(i * 16, k * 16, j * 16);
      }
    }
  }
}

void ChunkManager::draw(BlockRenderer renderer){

  for(int i = 0; i < M_WIDTH; i++){
    for(int j = 0; j < M_LENGTH; j++){
      for(int k = 0; k < M_HEIGHT; k++){
        chunks[i][k][j].draw(renderer);
      }
    }
  }
}

void ChunkManager::addHeight(std::vector<int> heights){

  for(int i = 0; i < M_WIDTH * 16; i++){
    for(int j = 0; j < M_LENGTH * 16; j++){
      int height = heights[i * M_LENGTH * 16 + j];

      int chunkLevels = height / 16;

      for(int k = 0; k < chunkLevels; k++){
        std::cout << "CHUNKS " << i/16 << " " << k << " " << j / 16 << std:: endl;
        chunks[i / 16][2][j / 16].addHeight(i % 16,16,j % 16);
      }

      chunks[i / 16][chunkLevels][j / 16].addHeight(i % 16,chunkLevels % 16,j % 16);
    }
  }
}
