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
  for(int length = 0; length < M_LENGTH; length ++){
    std::vector<std::shared_ptr<HeightChunk>> temp;
    for(int width = 0; width < M_WIDTH; width ++){
      temp.emplace_back(std::make_shared<HeightChunk>(width, length, centerX + 16 * width, centerY + 16 * length));
    }
    m_heightChunks.emplace_back(temp);
  }
  std::cout << "Complete Height Generation" << std::endl;
}

bool ChunkManager::hasProcess(){
  for(int i = 0; i < M_LENGTH; i++){
    for(int j = 0; j < M_WIDTH; j++){
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
    initMesh(0, 0, M_WIDTH, M_LENGTH);
  }


  if(isHeightReady && isNeedUpdate && isChunkReady){

  }
    for(int length = 0; length < M_LENGTH; length++){
      for(int width = 0; width < M_WIDTH; width++){

      if(m_heightChunks[length][width].get() != nullptr && m_heightChunks[length][width].get()->isMeshReady()){
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
      if(i == length - 1){
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
      if(j == width - 1){
        left = m_heightChunks[i][j - 1];
        if(!left.get()->isHeightReady()){
          continue;
        }
      }
      if(i > 0 && i < length - 1){
        front = m_heightChunks[i-1][j];
        back = m_heightChunks[i+1][j];
        if(!front.get()->isHeightReady()){
          continue;
        }
      }
      if(j > 0 && j < width - 1){
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
  for(int width = 0; width < M_WIDTH; width++){
    for(int length = 0; length < M_LENGTH; length++){
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
  for(int i = 0; i < M_LENGTH; i++){
    for(int j = 0; j < M_WIDTH; j++){
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

void ChunkManager::waitForHeight(int firstWidth, int firstLength, int secondWidth, int secondLength, SIGNAL signal){
  m_heightChunks[firstLength][firstWidth].get()->generateHeight();
  switch(signal){
    case SIGNAL::LEFT:
    //std::cout << "LEFT" << std::endl;

      m_heightChunks[secondLength][secondWidth].get()->addLeftMesh(m_heightChunks[firstLength][firstWidth]);
      break;
    case SIGNAL::RIGHT:
    //std::cout << "RIGHT" << std::endl;

      m_heightChunks[secondLength][secondWidth].get()->addRightMesh(m_heightChunks[firstLength][firstWidth]);
      break;
    case SIGNAL::FRONT:
    //std::cout << "FRONT" << std::endl;
      m_heightChunks[secondLength][secondWidth].get()->addFrontMesh(m_heightChunks[firstLength][firstWidth]);
      break;
    case SIGNAL::BACK:
    //std::cout << "BACK" << std::endl;

      m_heightChunks[secondLength][secondWidth].get()->addBackMesh(m_heightChunks[firstLength][firstWidth]);
      break;
    default:
      break;
  };
}

void ChunkManager::processBack(){
  processLock.lock();
  for(int length = 0; length < M_LENGTH - 1; length ++ ){
    for(int width = 0; width < M_WIDTH; width ++ ){
        m_heightChunks[length][width] = m_heightChunks[length + 1][width];
    }
  }
  updateChunks(0, M_LENGTH - 2, M_WIDTH, M_LENGTH - 1);

  for(int width = 0; width < M_WIDTH; width++){
    int newWidth = m_heightChunks[M_LENGTH - 1][width].get()->getWidth();
    int newLength = m_heightChunks[M_LENGTH - 1][width].get()->getLength() + 1;
    int newCenterX = m_heightChunks[M_LENGTH - 1][width].get()->getInitWidth();
    int newCenterY = m_heightChunks[M_LENGTH - 1][width].get()->getInitLength() + 16;
     m_heightChunks[M_LENGTH - 1][width] = std::make_shared<HeightChunk>(newWidth, newLength, newCenterX, newCenterY);
     // Build the height
	 ThreadPool::getInstance(0)->submit([this, width] {waitForHeight(width, M_LENGTH - 1, width, M_LENGTH - 2, SIGNAL::BACK); });
  }
  processLock.unlock();
}

void ChunkManager::processFront(){
  processLock.lock();
  for(int length = M_LENGTH - 1; length > 0; length -- ){
    for(int width = 0; width < M_WIDTH; width ++ ){
        m_heightChunks[length][width] = m_heightChunks[length-1][width];
    }
  }
  updateChunks(0, 1, M_WIDTH, 2);

  for(int width = 0; width < M_WIDTH; width++){
    int newWidth = m_heightChunks[0][width].get()->getWidth();
    int newLength = m_heightChunks[0][width].get()->getLength() - 1;
    int newCenterX = m_heightChunks[0][width].get()->getInitWidth();
    int newCenterY = m_heightChunks[0][width].get()->getInitLength() - 16;
     m_heightChunks[0][width] = std::make_shared<HeightChunk>(newWidth, newLength, newCenterX, newCenterY);
    // Build the height
	 ThreadPool::getInstance(0)->submit([this, width] {waitForHeight(width, 0, width, 1, SIGNAL::FRONT); });
     // Set the mesh
  }
  processLock.unlock();
}

void ChunkManager::processLeft(){
  processLock.lock();
  for(int width = M_WIDTH - 1; width > 0; width -- ){
    for(int length = 0; length < M_LENGTH; length ++ ){
        m_heightChunks[length][width] = m_heightChunks[length][width-1];
    }
  }
  updateChunks(1, 0, 2, M_LENGTH);

  for(int length = 0; length < M_LENGTH; length++){
    int newWidth = m_heightChunks[length][0].get()->getWidth() - 1;
    int newLength = m_heightChunks[length][0].get()->getLength();
    int newCenterX = m_heightChunks[length][0].get()->getInitWidth() - 16;
    int newCenterY = m_heightChunks[length][0].get()->getInitLength();
    m_heightChunks[length][0] = std::make_shared<HeightChunk>(newWidth, newLength, newCenterX, newCenterY);
    // Build the height
	ThreadPool::getInstance(0)->submit([this, length] {waitForHeight(0, length, 1, length, SIGNAL::LEFT); });
    // Set the mesh
  }
  processLock.unlock();
}

void ChunkManager::processRight(){
  processLock.lock();
  for(int width = 0; width < M_WIDTH - 1; width ++ ){
    for(int length = 0; length < M_LENGTH; length ++ ){
        m_heightChunks[length][width] = m_heightChunks[length][width+1];
    }
  }
  updateChunks(M_WIDTH - 2, 0, M_WIDTH - 1, M_LENGTH);
  for(int length = 0; length < M_LENGTH; length++){
    int newWidth = m_heightChunks[length][M_WIDTH - 1].get()->getWidth() + 1;
    int newLength = m_heightChunks[length][M_WIDTH - 1].get()->getLength();
    int newCenterX = m_heightChunks[length][M_WIDTH - 1].get()->getInitWidth() + 16;
    int newCenterY = m_heightChunks[length][M_WIDTH - 1].get()->getInitLength();
     m_heightChunks[length][M_WIDTH - 1] = std::make_shared<HeightChunk>(newWidth, newLength, newCenterX, newCenterY);
     // Build the height
	 ThreadPool::getInstance(0)->submit([this, length] {waitForHeight(M_WIDTH - 1, length, M_WIDTH - 2, length, SIGNAL::RIGHT); });
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

void ChunkManager::moveFront(int num){
  for(int i = 0; i < num; i++){
    moveFront();
  }
}

void ChunkManager::moveBack(int num){
  for(int i = 0; i < num; i++){
    moveBack();
  }
}

void ChunkManager::moveLeft(int num){
  for(int i = 0; i < num; i++){
    moveLeft();
  }
}

void ChunkManager::moveRight(int num){
  for(int i = 0; i < num; i++){
    moveRight();
  }
}
