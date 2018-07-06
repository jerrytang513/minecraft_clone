#include "chunkRenderer.h"
#include "../Chunk/chunkManager.h"
#include "direction.h"

ChunkRenderer::ChunkRenderer(){}

ChunkMesh ChunkRenderer::getChunkMesh(ChunkManager& chunks){
  m_chunks = chunks.getChunks();

  m_width = m_chunks.size();
  m_height = m_chunks[0].size();
  m_length = m_chunks[0][0].size();

  for(int i = 0; i < m_width; i ++){
    for(int j = 0; j < m_height; j++){
      for(int k = 0; j < m_length; k++){
        generateChunkMesh(i, j, k);
      }
    }
  }
}

// This Function Will check the other chunk block and
bool ShouldAddFace(int chunkX, int chunkY, int chunkZ, int i, int j, int k){
  if(chunkX < 0 || chunkX >= m_width || chunkY < 0 || chunkY >= m_height || chunkZ < 0 || chunk Z >= m_length)
    return true;
  return m_chunk[chunkX][chunkY][chunkZ][i][j][k].isVisible;
}

void generateChunkMesh(int chunkX, int chunkY, int chunkZ){
  BlockChunk block = m_chunks[i][j][k];
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
// TODO Generate A Mesh for this chunk block


}
