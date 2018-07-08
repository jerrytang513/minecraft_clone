#include "chunkManager.h"

ChunkManager::ChunkManager(int width, int length,std::vector<int> heights):M_WIDTH{width},M_LENGTH{length}{
  M_HEIGHT = 20;
  std::vector<std::vector<std::vector<BlockChunk>>> temp {std::vector<std::vector<std::vector<BlockChunk>>>(M_WIDTH, std::vector<std::vector<BlockChunk>>(M_HEIGHT,std::vector<BlockChunk>(M_LENGTH,BlockChunk())))};
  m_chunks = temp;
  /*
  for(int i = 0; i < M_WIDTH; i++){
    std::vector<std::vector<BlockChunk>> height;
    for(int j = 0; j < M_HEIGHT; j++){

      std::vector<BlockChunk> len;
      for(int k = 0; k < M_LENGTH; k++){
        len.emplace_back(BlockChunk());
      }
      height.emplace_back(len);
    }
    m_chunks.emplace_back(height);
  }*/
  initializeHeights();
  addHeight(heights);
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

void ChunkManager::draw(ChunkRenderer renderer){
  std::vector<ChunkMesh*> meshes;
  if(renderList.size() == 0)
    return;
  for(int i = 0; i < renderList.size(); i++){
    meshes.emplace_back(m_chunks[renderList[i].coord.x][renderList[i].coord.y][renderList[i].coord.z].getMesh());
  }
  renderer.draw(meshes);
}

void ChunkManager::addHeight(std::vector<int> heights){
  for(int i = 0; i < M_WIDTH * 16; i++){
    for(int j = 0; j < M_LENGTH * 16; j++){
      int height = heights[i * M_LENGTH * 16 + j];
      if( height < 0)
        height *= -1;
      if ( height > M_HEIGHT * 16)
        height = M_HEIGHT * 16 - 1;
      int chunkLevels = height / 16;
      for(int k = 0; k < chunkLevels; k++){
        m_chunks[i / 16][k][j / 16].setIsActive(true);
        m_chunks[i / 16][k][j / 16].addHeight(i % 16,16,j % 16);
      }
      m_chunks[i / 16][chunkLevels][j / 16].setIsActive(true);
      m_chunks[i / 16][chunkLevels][j / 16].addHeight(i % 16,height % 16,j % 16);
    }
  }
}

const std::vector<std::vector<std::vector<BlockChunk>>> ChunkManager::getChunks(){
  return m_chunks;
}

void ChunkManager::initMesh(){
//  ThreadPool pool(8);
//  pool.init();
  TextureManager::getInstance();

  for(int i = 0; i < M_WIDTH; i ++){
    for(int j = 0; j < M_HEIGHT; j++){
  		for (int k = 0; k < M_LENGTH; k++) {
        //std::cout << "I " << i << " J " << j << " K " << k << std::endl;
        if (m_chunks[i][j][k].getIsActive()) {

  				//  auto future = pool.submit(&ChunkManager::generateChunkMesh,i,j,k);
  				ThreadPool::getInstance()->submit([this, i, j, k] { generateChunkMesh(i, j, k); });
          //generateChunkMesh(i, j, k);
  			}
  		}
    }
  }
//  pool.shutdown();
TextureManager::getInstance();

}

// This Function Will check the other chunk block and
bool ChunkManager::shouldAddFace(int chunkX, int chunkY, int chunkZ){
  if(chunkX < 0 || chunkX >= M_WIDTH || chunkY < 0 || chunkY >= M_HEIGHT || chunkZ < 0 || chunkZ >= M_LENGTH)
    return true;
  return false;
}

void ChunkManager::generateChunkMesh(int chunkX, int chunkY, int chunkZ) {
	std::vector<std::vector<std::vector<BlockInfo>>>& block = m_chunks[chunkX][chunkY][chunkZ].getBlockInfo();
  m_chunks[chunkX][chunkY][chunkZ].setIsReady(false);
  std::vector<std::vector<int>>& highest = m_chunks[chunkX][chunkY][chunkZ].getHighest();
	for (int i = 0; i < 16; i++) {
		for (int k = 0; k < 16; k++) {
      for (int j = 0; j < 16; j++) {

    // std::cout << "I " << i << "J " << j << " K " << k << std::endl;
				if (!block[i][j][k].visible)
					continue;
				// TODO Finish up the addFace Function
        if (i == 0) {
					if (shouldAddFace(chunkX - 1, chunkY, chunkZ) || !m_chunks[chunkX - 1][chunkY][chunkZ].getBlockInfo()[15][j][k].visible)
						m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::LEFT);
				}
				else {
					if (!block[i - 1][j][k].visible)
						m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::LEFT);
				}

				if (i == 15) {
					if (shouldAddFace(chunkX + 1, chunkY, chunkZ) ||  !m_chunks[chunkX + 1][chunkY][chunkZ].getBlockInfo()[0][j][k].visible)
						m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::RIGHT);
				}
				else {
					if (!block[i + 1][j][k].visible)
						m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::RIGHT);
				}

				if (j == 0) {
					if (shouldAddFace(chunkX, chunkY - 1, chunkZ) ||  !m_chunks[chunkX][chunkY -1][chunkZ].getBlockInfo()[i][15][k].visible)
						m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::DOWN);
				}
				else {
					if (!block[i][j - 1][k].visible)
						m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::DOWN);
				}

				if (j == 15) {
					if (shouldAddFace(chunkX, chunkY + 1, chunkZ) ||  !m_chunks[chunkX][chunkY + 1][chunkZ].getBlockInfo()[i][0][k].visible)
						m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::UP);
				}
				else {
					if (!block[i][j + 1][k].visible)
						m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::UP);
				}

				if (k == 0) {
					if (shouldAddFace(chunkX, chunkY, chunkZ - 1) ||  !m_chunks[chunkX][chunkY][chunkZ - 1].getBlockInfo()[i][j][15].visible)
						m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::BACK);
				}
				else {
					if (!block[i][j][k - 1].visible)
						m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::BACK);
				}

				if (k == 15) {
					if (shouldAddFace(chunkX, chunkY, chunkZ + 1) ||  !m_chunks[chunkX][chunkY][chunkZ + 1].getBlockInfo()[i][j][0].visible)
						m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::FRONT);
				}
				else {
					if (!block[i][j][k + 1].visible)
						m_chunks[chunkX][chunkY][chunkZ].addFace(i, j, k, Direction::FRONT);
				}
			}
		}
	}
  if(m_chunks[chunkX][chunkY][chunkZ].getVerticeCount() != 0){
    renderList.emplace_back(Vec3D(chunkX, chunkY, chunkZ));
    m_chunks[chunkX][chunkY][chunkZ].setIsReady(true);
  }
}
