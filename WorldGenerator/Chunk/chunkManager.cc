#include "chunkManager.h"

ChunkManager::ChunkManager(int width, int length) :M_WIDTH{ width }, M_LENGTH{ length }, isHeightReady{ false }, isChunkReady{ false }, isProcessing{ false }, isNeedUpdate{true}{

  // These two values are use to generate the height, it is m_hightChunks[0][0] location.
  centerX = 100000;
  centerY = 100000;
  for(int length = 0; length < 16; length ++){
    std::vector<std::shared_ptr<HeightChunk>> temp;
    for(int width = 0; width < 16; width ++){
      temp.emplace_back(std::make_shared<HeightChunk>(width, length, centerX + 16 * width, centerY + 16 * length));
    }
    m_heightChunks.emplace_back(temp);
  }
  std::cout << "Complete Height Generation" << std::endl;

}

// ********** testing
void ChunkManager::render(ChunkRenderer renderer){
  std::vector<std::shared_ptr<ChunkMesh>> meshes;
  for(int width = 0; width < 16; width ++){
    for(int length = 0; length < 16; length ++){
      if(!m_heightChunks[length][width].get()->isProcessing() && !m_heightChunks[length][width].get()->isMeshReady()){
        ThreadPool::getInstance(0)->submit([this, length, width] {m_heightChunks[length][width].get()->testGenMesh();});
      } else if(m_heightChunks[length][width].get()->isMeshReady()){

		  std::vector<std::shared_ptr<ChunkMesh>> temp = m_heightChunks[length][width].get()->getChunkMesh();
		  std::vector<std::shared_ptr<ChunkMesh>>::iterator tbegin = temp.begin();
		  std::vector<std::shared_ptr<ChunkMesh>>::iterator tend = temp.end();

		  meshes.insert(meshes.end(), tbegin, tend);
	  }
    }
  }
  renderer.draw(meshes);
}

// ********* Testing
void ChunkManager::draw(ChunkRenderer renderer){
  std::vector<std::shared_ptr<ChunkMesh>> meshes;

  if(!isHeightReady && !isProcessing){
    ThreadPool::getInstance(0)->submit([this] {initHeight();});
  }

  // Check if height info is ready, so can generate chunk mesh
  // If chunk Mesh is already ready, than don't need to do that again
  //if(isHeightReady && !isChunkReady){
    initMesh(0, 0, 16, 16);
    //isChunkReady = true;
  //}

  if(isHeightReady && isNeedUpdate && isChunkReady){

  }

    for(int length = 0; length < 16; length++){
      for(int width = 0; width < 16; width++){
      if(m_heightChunks[length][width].get()->isMeshReady() && !m_heightChunks[length][width].get()->isNeedUpdate()){
        std::vector<std::shared_ptr<ChunkMesh>> temp = m_heightChunks[length][width].get()->getChunkMesh();
        std::vector<std::shared_ptr<ChunkMesh>>::iterator tbegin = temp.begin();
        std::vector<std::shared_ptr<ChunkMesh>>::iterator tend = temp.end();
        if(temp.size() != 0){
          meshes.insert(meshes.end(), tbegin, tend);
        }
      }
    }
  }
  renderer.draw(meshes);
}

void ChunkManager::addChunks(){
  for(int width = 0; width < 16; width++){
    for(int length = 0; length < 16; length++){
      if(m_heightChunks[width][length].get()->isMeshReady() && !m_heightChunks[width][length].get()->isNeedUpdate()){
        std::vector<std::shared_ptr<ChunkMesh>> temp = m_heightChunks[width][length].get()->getChunkMesh();
        std::vector<std::shared_ptr<ChunkMesh>>::iterator tbegin = temp.begin();
        std::vector<std::shared_ptr<ChunkMesh>>::iterator tend = temp.end();
        if(temp.size() != 0)
          renderList.insert(renderList.end(), tbegin, tend);
      }
    }
  }
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

void ChunkManager::initHeight(){
  isProcessing = true;
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
		m_heightChunks[i][j].get()->generateHeight();
    }
  }
  isHeightReady = true;
  isProcessing = false;
}

void ChunkManager::initMesh(int startWidth, int startLength, int width, int length){
  TextureManager::getInstance();
  for(int i = startLength; i < length; i ++){
    for(int j = startWidth; j < width; j++){
      if(!m_heightChunks[i][j].get()->isHeightReady() || !m_heightChunks[i][j].get()->isNeedUpdate() || m_heightChunks[i][j].get()->isProcessing())
        continue;
    //  std::cout << " I " << i << " J " << j << std::endl;
      std::shared_ptr<HeightChunk> left;
      std::shared_ptr<HeightChunk> right;
      std::shared_ptr<HeightChunk> front;
      std::shared_ptr<HeightChunk> back;
      if(i == 0){
        back = m_heightChunks[i+1][j];
        // Test if processsing matters:
        if(!back.get()->isHeightReady() || back.get()->isNeedUpdate())
          continue;
      }
      if(i == 15){
        front = m_heightChunks[i-1][j];
        if(!front.get()->isHeightReady() || front.get()->isNeedUpdate())
          continue
      }
      if(j == 0){
        right = m_heightChunks[i][j + 1];
        if(!right.get()->isHeightReady() || right.get()->isNeedUpdate())
          continue
      }
      if(j == 15){
        left = m_heightChunks[i][j - 1];
        if(!left.get()->isHeightReady() || left.get()->isNeedUpdate())
          continue
      }
      if(i > 0 && i < 15){
        front = m_heightChunks[i-1][j];
        back = m_heightChunks[i+1][j];
        if(!front.get()->isHeightReady() || front.get()->isNeedUpdate() || !back.get()->isHeightReady() || back.get()->isNeedUpdate())
          continue
      }
      if(j > 0 && j < 15){
        left = m_heightChunks[i][j-1];
        right = m_heightChunks[i][j+1];
      }

      // Additional safe guard

      // Generate Chunk Mesh
	  ThreadPool::getInstance(0)->submit([this, i, j, left, right, front, back] { m_heightChunks[i][j].get()->updateHeightChunk(left,right,front,back); });
      //m_heightChunks[i][j].get()->updateHeightChunk(left,right,front,back);

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
  //  renderList.emplace_back(Vec3D(chunkX, chunkY, chunkZ));
    m_chunks[chunkX][chunkY][chunkZ].setIsReady(true);
  }
}

void ChunkManager::updateChunks(int startWidth, int startLength, int width, int length){
  for(int i = startLength; i < length; i++){
    for(int j = startWidth; j < width; j++){
      m_heightChunks[i][j].get()->clearMesh();
    }
  }
}

void ChunkManager::moveFront(){
  std::cout << "FR" << std::endl;

  updateChunks(0, 15, 16, 16);
  for(int width = 15; width > 0; width -- ){
    for(int length = 0; length < 16; length ++ ){
		    m_heightChunks[length][width] = m_heightChunks[length][width - 1];
    }
  }

  for(int width = 0; width < 16; width++){
    int newWidth = m_heightChunks[14][width].get()->getWidth();
    int newLength = m_heightChunks[14][width].get()->getLength() + 1;
	   m_heightChunks[15][width] = std::make_shared<HeightChunk>(newWidth, newLength, centerX + 16 * newWidth, centerY + 16 * newLength);
     // Build the height
     m_heightChunks[15][width].get()->generateHeight();
     // Set the mesh
  }
  initMesh(0, 14, 16, 16);
}


void ChunkManager::moveBack(){
  std::cout << "BA" << std::endl;

  updateChunks(0, 0, 16, 1);
  for(int length = 15; length > 0; length -- ){
    for(int width = 0; width < 16; width ++ ){
		    m_heightChunks[length][width] = m_heightChunks[length-1][width];
    }
  }

  for(int width = 0; width < 16; width++){
    int newWidth = m_heightChunks[1][width].get()->getWidth();
    int newLength = m_heightChunks[1][width].get()->getLength() - 1;
	   m_heightChunks[0][width] = std::make_shared<HeightChunk>(newWidth, newLength, centerX + 16 * newWidth, centerY + 16 * newLength);
     // Build the height
     m_heightChunks[0][width].get()->generateHeight();
     // Set the mesh
  }
  initMesh(0, 0, 16, 2);
}

void ChunkManager::moveLeft(){
  std::cout << "LE" << std::endl;
  updateChunks(0, 0, 1, 16);
  for(int width = 15; width > 0; width -- ){
    for(int length = 0; length < 16; length ++ ){
		    m_heightChunks[length][width] = m_heightChunks[length][width-1];
    }
  }

  for(int length = 0; length < 16; length++){
    int newWidth = m_heightChunks[length][1].get()->getWidth() - 1;
    int newLength = m_heightChunks[length][1].get()->getLength();
	   m_heightChunks[length][0] = std::make_shared<HeightChunk>(newWidth, newLength, centerX + 16 * newWidth, centerY + 16 * newLength);
     // Build the height
     m_heightChunks[length][0].get()->generateHeight();
     // Set the mesh
  }
  initMesh(0, 0, 2, 16);
}

void ChunkManager::moveRight(){
  std::cout << "RI" << std::endl;

  updateChunks(15, 0, 16, 16);
  for(int width = 0; width < 15; width ++ ){
    for(int length = 0; length < 16; length ++ ){
		    m_heightChunks[length][width] = m_heightChunks[length][width+1];
    }
  }

  for(int length = 0; length < 16; length++){
    int newWidth = m_heightChunks[length][14].get()->getWidth() + 1;
    int newLength = m_heightChunks[length][14].get()->getLength();
	   m_heightChunks[length][15] = std::make_shared<HeightChunk>(newWidth, newLength, centerX + 16 * newWidth, centerY + 16 * newLength);
     // Build the height
     m_heightChunks[length][15].get()->generateHeight();
     // Set the mesh
  }
  initMesh(14, 0, 16, 16);
}
