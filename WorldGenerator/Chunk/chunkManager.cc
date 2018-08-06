#include "chunkManager.h"

ChunkManager::ChunkManager(int width, int length) :
  M_WIDTH{ width },
  M_LENGTH{ length },
  isHeightReady{ false },
  isChunkReady{ false },
  isProcessing{ false },
  isNeedUpdate{true}{

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

bool ChunkManager::hasProcess(){
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      if(!m_heightChunks[i][j].get()->isMeshReady())
        return true;
    }
  }
  return false;
}

void ChunkManager::checkSignal(){
  boardLock.lock();
  bool processSignal = hasProcess();
  if(!processSignal && !signal_queue.empty()){
    // make some changes to the chunk map
    SIGNAL curSignal = signal_queue.front();
    signal_queue.pop();

    switch(curSignal){
      case SIGNAL::FRONT:
        processFront();
        break;
      case SIGNAL::BACK:
        processBack();
        break;
      case SIGNAL::LEFT:
        processLeft();
        break;
      case SIGNAL::RIGHT:
        processRight();
        break;
      default:
        break;
    }
  }
  boardLock.unlock();
}
void ChunkManager::draw(ChunkRenderer renderer){
  std::vector<std::shared_ptr<ChunkMesh>> meshes;

  checkSignal(); 

  if(!isHeightReady && !isProcessing){
    isProcessing = true;
    initHeight();
  }
  // Check if height info is ready, so can generate chunk mesh
  // If chunk Mesh is already ready, than don't need to do that again
  if(isHeightReady){
    ThreadPool::getInstance(0)->submit([this] { initMesh(0, 0, 16, 16); });
  }

  if(isHeightReady && isNeedUpdate && isChunkReady){

  }
    for(int length = 0; length < 16; length++){
      for(int width = 0; width < 16; width++){
      if(m_heightChunks[length][width].get()->isMeshReady() && !m_heightChunks[length][width].get()->isNeedUpdate()){
        std::vector<std::shared_ptr<ChunkMesh>> temp = m_heightChunks[length][width].get()->getChunkMesh();
        if(temp.size() == 0)
          continue;
        std::vector<std::shared_ptr<ChunkMesh>>::iterator tbegin = temp.begin();
        std::vector<std::shared_ptr<ChunkMesh>>::iterator tend = temp.end();
        meshes.insert(meshes.end(), tbegin, tend);
      }
    }
  }
  if(meshes.size() != 0)
    renderer.draw(meshes);

}

void ChunkManager::initMesh(int startWidth, int startLength, int width, int length){
  TextureManager::getInstance();
  for(int i = startLength; i < length; i ++){
    for(int j = startWidth; j < width; j++){
      if(!m_heightChunks[i][j].get()->isHeightReady() || !m_heightChunks[i][j].get()->isNeedUpdate() || m_heightChunks[i][j].get()->isProcessing())
        continue;
      std::shared_ptr<HeightChunk> left;
      std::shared_ptr<HeightChunk> right;
      std::shared_ptr<HeightChunk> front;
      std::shared_ptr<HeightChunk> back;
      if(i == 0){
        back = m_heightChunks[i+1][j];
        if(!back.get()->isHeightReady()){
          continue;
        }
      }
      if(i == 15){
        front = m_heightChunks[i-1][j];
        if(!front.get()->isHeightReady()){
          continue;

        }
      }
      if(j == 0){
        right = m_heightChunks[i][j + 1];
        if(!right.get()->isHeightReady()){
          continue;
        }
      }
      if(j == 15){
        left = m_heightChunks[i][j - 1];
        if(!left.get()->isHeightReady()){
          continue;
        }
      }
      if(i > 0 && i < 15){
        front = m_heightChunks[i-1][j];
        back = m_heightChunks[i+1][j];
        if(!front.get()->isHeightReady()){
          continue;
        }
      }
      if(j > 0 && j < 15){
        left = m_heightChunks[i][j-1];
        right = m_heightChunks[i][j+1];
        if(!left.get()->isHeightReady()){
          continue;
        }

      }
      // Generate Chunk Mesh
    m_heightChunks[i][j].get()->setIsProcessing(true);
	  ThreadPool::getInstance(0)->submit([this, i, j, left, right, front, back] { m_heightChunks[i][j].get()->updateHeightChunk(left,right,front,back); });
      //m_heightChunks[i][j].get()->updateHeightChunk(left,right,front,back);

    }
  }
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

void ChunkManager::initHeight(){
  isProcessing = true;
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
		ThreadPool::getInstance(0)->submit([this, i, j] { m_heightChunks[i][j].get()->generateHeight(); });
    }
  }
  isHeightReady = true;
  isProcessing = false;
}

void ChunkManager::updateChunks(int startWidth, int startLength, int width, int length){
  /*for(int i = startLength; i < length; i++){
    for(int j = startWidth; j < width; j++){
      m_heightChunks[i][j].get()->clearMesh();
    }
  }*/

}

void ChunkManager::processBack(){
  processLock.lock();
  for(int length = 0; length < 15; length ++ ){
    for(int width = 0; width < 16; width ++ ){
        m_heightChunks[length][width] = m_heightChunks[length + 1][width];
    }
  }
  updateChunks(0, 14, 16, 15);

  for(int width = 0; width < 16; width++){
    int newWidth = m_heightChunks[15][width].get()->getWidth();
    int newLength = m_heightChunks[15][width].get()->getLength() + 1;
    int newCenterX = m_heightChunks[15][width].get()->getInitWidth();
    int newCenterY = m_heightChunks[15][width].get()->getInitLength() + 16;
     m_heightChunks[15][width] = std::make_shared<HeightChunk>(newWidth, newLength, newCenterX, newCenterY);
     // Build the height
     ThreadPool::getInstance(0)->submit([this, width] { m_heightChunks[15][width].get()->generateHeight();});
     // Set the mesh
  }
  processLock.unlock();
}

void ChunkManager::processFront(){
  processLock.lock();
  for(int length = 15; length > 0; length -- ){
    for(int width = 0; width < 16; width ++ ){
        m_heightChunks[length][width] = m_heightChunks[length-1][width];
    }
  }
  updateChunks(0, 1, 16, 2);

  for(int width = 0; width < 16; width++){
    int newWidth = m_heightChunks[0][width].get()->getWidth();
    int newLength = m_heightChunks[0][width].get()->getLength() - 1;
    int newCenterX = m_heightChunks[0][width].get()->getInitWidth();
    int newCenterY = m_heightChunks[0][width].get()->getInitLength() - 16;
     m_heightChunks[0][width] = std::make_shared<HeightChunk>(newWidth, newLength, newCenterX, newCenterY);
    // Build the height
    ThreadPool::getInstance(0)->submit([this, width] { m_heightChunks[0][width].get()->generateHeight();});
     // Set the mesh
  }
  processLock.unlock();
}

void ChunkManager::processLeft(){
  processLock.lock();
  for(int width = 15; width > 0; width -- ){
    for(int length = 0; length < 16; length ++ ){
        m_heightChunks[length][width] = m_heightChunks[length][width-1];
    }
  }
  updateChunks(1, 0, 2, 16);

  for(int length = 0; length < 16; length++){
    int newWidth = m_heightChunks[length][0].get()->getWidth() - 1;
    int newLength = m_heightChunks[length][0].get()->getLength();
    int newCenterX = m_heightChunks[length][0].get()->getInitWidth() - 16;
    int newCenterY = m_heightChunks[length][0].get()->getInitLength();
    m_heightChunks[length][0] = std::make_shared<HeightChunk>(newWidth, newLength, newCenterX, newCenterY);
    // Build the height
    ThreadPool::getInstance(0)->submit([this, length] { m_heightChunks[length][0].get()->generateHeight();});
    // Set the mesh
  }
  processLock.unlock();
}

void ChunkManager::processRight(){
  processLock.lock();
  for(int width = 0; width < 15; width ++ ){
    for(int length = 0; length < 16; length ++ ){
        m_heightChunks[length][width] = m_heightChunks[length][width+1];
    }
  }
  updateChunks(14, 0, 15, 16);
  for(int length = 0; length < 16; length++){
    int newWidth = m_heightChunks[length][14].get()->getWidth() + 1;
    int newLength = m_heightChunks[length][14].get()->getLength();
     m_heightChunks[length][15] = std::make_shared<HeightChunk>(newWidth, newLength, centerX + 16 * newWidth, centerY + 16 * newLength);
     // Build the height
     ThreadPool::getInstance(0)->submit([this, length] { m_heightChunks[length][15].get()->generateHeight();});
  }
  processLock.unlock();
}

void ChunkManager::moveBack(){
  signal_queue.push(SIGNAL::BACK);
}

void ChunkManager::moveFront(){
  signal_queue.push(SIGNAL::FRONT);
}

void ChunkManager::moveLeft(){
  signal_queue.push(SIGNAL::LEFT);
}

void ChunkManager::moveRight(){
  signal_queue.push(SIGNAL::RIGHT);
}
