#include "chunkManager.h"


ChunkManager::ChunkManager(int width, int length):M_WIDTH{width},M_LENGTH{length},chunks{std::vector<std::vector<std::vector<BlockChunk>>>(2, std::vector<std::vector<BlockChunk>>(2,std::vector<BlockChunk>(2,BlockChunk())))}{
}
ChunkManager::ChunkManager(int width, int length,std::vector<int> heights):M_WIDTH{width},M_LENGTH{length}{

  std::vector<std::vector<std::vector<BlockChunk>>> temp {std::vector<std::vector<std::vector<BlockChunk>>>(M_WIDTH, std::vector<std::vector<BlockChunk>>(M_HEIGHT,std::vector<BlockChunk>(M_LENGTH,BlockChunk())))};
  m_chunks = temp;
  initializeHeights();
  addHeight(heights);
  std::cout << M_WIDTH << "  " << M_LENGTH << std::endl;
}

void ChunkManager::initializeHeights(){
  for(int i = 0; i < M_WIDTH; i++){
    for(int j = 0; j < M_LENGTH; j++){
      for(int k = 0; k < M_HEIGHT; k++){
        m_chunks[i][k][j].setConfig(i * 16, k * 16, j * 16);
      }
    }
  }
}

void ChunkManager::draw(BlockRenderer renderer){

  for(int i = 0; i < M_WIDTH; i++){
    for(int j = 0; j < M_LENGTH; j++){
      for(int k = 0; k < M_HEIGHT; k++){
        m_chunks[i][k][j].draw(renderer);
      }
    }
  }
}

void ChunkManager::addHeight(std::vector<int> heights){

  for(int i = 0; i < M_WIDTH * 16; i++){
    for(int j = 0; j < M_LENGTH * 16; j++){

      int height = heights[i * M_LENGTH * 16 + j];
      std::cout << "i " << i << " j " << j << " height " << height << std::endl;
      int chunkLevels = height / 16;

      for(int k = 0; k < chunkLevels; k++){
        std::cout << "CHUNKS " << i/16 << " " << k << " " << j / 16 << std:: endl;
        m_chunks[i / 16][k][j / 16].addHeight(i % 16,16,j % 16);
      }
      std::cout << height % 16 << std::endl;
      m_chunks[i / 16][chunkLevels][j / 16].addHeight(i % 16,height % 16,j % 16);
    }
  }
}

const std::vector<std::vector<std::vector<BlockChunk>>>& ChunkManager::getChunks(){
  return m_chunks;
}

void ChunkManager::initMesh(){

  for(int i = 0; i < M_WIDTH; i ++){
    for(int j = 0; j < M_HEIGHT; j++){
      for(int k = 0; j < M_LENGTH; k++){
        generateChunkMesh(i, j, k);
      }
    }
  }
}

// This Function Will check the other chunk block and
bool ChunkManager::shouldAddFace(int chunkX, int chunkY, int chunkZ, int i, int j, int k){
  if(chunkX < 0 || chunkX >= m_width || chunkY < 0 || chunkY >= m_height || chunkZ < 0 || chunk Z >= m_length)
    return true;
  return m_chunk[chunkX][chunkY][chunkZ][i][j][k].isVisible;
}

void ChunkManager::generateChunkMesh(int chunkX, int chunkY, int chunkZ){
  BlockChunk block = m_chunks[chunkX][chunkY][chunkZ];
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      for(int k = 0; k < 16; k++){
        if(!block[i][j][k].isVisible)
          continue;
          // TODO Finish up the addFace Function
          if(i == 0){
            if(shouldAddFace(chunkX - 1, chunkY, chunkZ, 15, j, k))
              m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::LEFT);
          } else {
            if(!block[i-1][j][k].isVisible)
              m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::LEFT);
          }

          if(i == 15){
            if(shouldAddFace(chunkX + 1, chunkY, chunkZ, 0, j, k))
              m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::RIGHT);
          } else {
            if(!block[i+1][j][k].isVisible)
              m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::RIGHT);
          }

          if(j == 0){
              if(shouldAddFace(chunkX, chunkY - 1, chunkZ, i, 15, k))
                m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::DOWN);
          } else {
            if(!block[i][j-1][k].isVisible)
                m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::DOWN);
          }

          if(j == 15){
            if(shouldAddFace(chunkX, chunkY + 1, chunkZ, i, 0, k))
              m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::TOP);
          } else {
            if(!block[i][j+1][k].isVisible)
              m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::TOP);
          }

          if(k == 0){
              if(shouldAddFace(chunkX, chunkY, chunkZ - 1, i, j, 15))
                m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::BACK);
          } else {
              if(!block[i][j][k-1].isVisible)
                m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::BACK);
          }

          if(k == 15){
            if(shouldAddFace(chunkX, chunkY, chunkZ + 1, i, j, 0))
              m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::FRONT);
          } else {
            if(!block[i][j][k+1].isVisible)
              m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::FRONT);
          }
      }
    }
  }
