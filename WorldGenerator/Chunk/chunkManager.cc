#include "chunkManager.h"

ChunkManager::ChunkManager(int width, int length,std::vector<int> heights):M_WIDTH{width},M_LENGTH{length}{
  M_HEIGHT = 30;
  std::vector<std::vector<std::vector<BlockChunk>>> temp {std::vector<std::vector<std::vector<BlockChunk>>>(M_WIDTH, std::vector<std::vector<BlockChunk>>(M_HEIGHT,std::vector<BlockChunk>(M_LENGTH,BlockChunk())))};
  m_chunks = temp;

  initializeHeights();
  addHeight(heights);
}

ChunkManager::ChunkManager(int width, int length):M_WIDTH{width},M_LENGTH{length}{

  // These two values are use to generate the height, it is m_hightChunks[0][0] location.
  centerX = 100000;
  centerY = 100000;
  for(int width = 0; width < 16; width ++){
    std::vector<std::shared_ptr<HeightChunk>> temp;
    for(int length = 0; length < 16; length ++){
      temp.emplace_back(std::make_shared<HeightChunk>(width, length, centerX + 16 * width, centerY + 16 * length));
    }
    m_heightChunks.emplace_back(temp);
  }
  std::cout << "Complete Height Generation" << std::endl;

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
  std::cout << "Render Chunk Meshes " << std::endl;
  std::vector<ChunkMesh*> meshes;
  /*if(renderList.size() == 0)
    return;
  for(int i = 0; i < renderList.size(); i++){
  //  std::cout << "START" << std::endl;
    meshes.emplace_back(m_chunks[renderList[i].coord.x][renderList[i].coord.y][renderList[i].coord.z].getMesh());
  //  std::cout << "END" << std::endl;
  }
  renderer.draw(meshes);
  */
  for(int width = 0; width < 16; width++){
    for(int length = 0; length < 16; length++){
      std::vector<ChunkMesh*> temp = m_heightChunks[width][length].get()->getChunkMesh();
      if(temp.size() != 0)
        meshes.insert(meshes.end(), temp.begin(), temp.end());
    }
  }
  std::cout << " All Chunk Mesh received, ready to draw" << meshes.size() << std::endl;

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


  TextureManager::getInstance();
/*
  for(int i = 0; i < M_WIDTH; i ++){
    for(int j = 0; j < M_HEIGHT; j++){
  		for (int k = 0; k < M_LENGTH; k++) {
        if (m_chunks[i][j][k].getIsActive()) {
  				ThreadPool::getInstance()->submit([this, i, j, k] { generateChunkMesh(i, j, k); });
  			}
  		}
    }
  }
*/
  for(int i = 0; i < 16; i ++){
    for(int j = 0; j < 16; j++){
    //  std::cout << " I " << i << " J " << j << std::endl;
      std::shared_ptr<HeightChunk> left;
      std::shared_ptr<HeightChunk> right;
      std::shared_ptr<HeightChunk> front;
      std::shared_ptr<HeightChunk> back;
      if(i == 0){
        left = nullptr;
        right = m_heightChunks[i+1][j];
      }
      if(i == 15){
        right = nullptr;
        left = m_heightChunks[i-1][j];
      }
      if(j == 0){
        front = nullptr;
        back = m_heightChunks[i][j + 1];
      }
      if(j == 15){
        front = m_heightChunks[i][j - 1];
        back = nullptr;
      }
      if(i > 0 && i < 15){
        left = m_heightChunks[i-1][j];
        right = m_heightChunks[i+1][j];
      }
      if(j > 0 && j < 15){
        front = m_heightChunks[i][j-1];
        back = m_heightChunks[i][j+1];
      }
      // Generate Chunk Mesh
      m_heightChunks[i][j].get()->updateHeightChunk(left,right,front,back);

    }
  }
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
