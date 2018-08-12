#include "heightChunk.h"

HeightChunk::HeightChunk(int m_width, int m_length, int m_initWidth, int m_initLength):
  m_width{m_width},
  m_length{m_length},
  m_initWidth{m_initWidth},
  m_initLength{m_initLength},
  m_isHeightReady{false},
  m_isMeshReady{false},
  m_isNeedUpdate{true},
  m_isProcessing{false}
  {}

BlockChunk& HeightChunk::getBlockChunk(int height){
  return m_chunks[height];
}

void HeightChunk::init(){
  max_height = std::max(max_height, TypeGen::getInstance().getMinHeight());
  std::cout << max_height << std::endl;
  int total_chunks = max_height / 16;
  int left_over = max_height % 16;

  for(int i = 0; i < total_chunks; i++){
    std::vector<int> temp = m_height;
    std::vector<int>::iterator tbegin = temp.begin();
    std::vector<int>::iterator tend = temp.end();
	  std::for_each(tbegin, tend, [i](int& val) {
      if((val - i * 16) > 0){
        if((val - i * 16) < 16){
          val -= i * 16;
        } else {
          val = 16;
        }
      } else {
        val = 0;
      }
    });
    m_chunks.emplace_back(BlockChunk(m_width * 16, i * 16, m_length * 16, temp, m_height));
  }
  if(left_over > 0){
    std::vector<int> temp = m_height;
    std::vector<int>::iterator tbegin = temp.begin();
    std::vector<int>::iterator tend = temp.end();
    std::for_each(tbegin, tend, [total_chunks](int& val) {
      if((val - total_chunks * 16) > 0){
        if((val - total_chunks * 16) < 16){
          val -= total_chunks * 16;
        } else {
          val = 16;
        }
      } else {
        val = 0;
      }
    });
    m_chunks.emplace_back(BlockChunk(m_width * 16, total_chunks * 16, m_length * 16, temp, m_height));
  }


  m_isHeightReady = true;
}


void HeightChunk::generateHeight(){
  NoiseGenerator& ng = NoiseGenerator::getInstance();
  // Generate all the heights, and get the maximum height.
  for(int length = 0; length < 16; length ++ ){
    for(int width = 0; width < 16; width ++ ){
      int new_height = ng.getHeight(width + m_initWidth, length + m_initLength);
      max_height = max_height < new_height ? new_height : max_height;
      m_height.emplace_back(new_height);
    }
  }
  init();
}

void HeightChunk::testBlockChunksFrontBack(int height, std::shared_ptr<HeightChunk> front,  std::shared_ptr<HeightChunk>  back){

  BlockChunk& blockChunk = m_chunks[height];
  std::vector<std::vector<std::vector<BlockInfo>>>& block = blockChunk.getBlockInfo();
  bool hasFront = (front.get() != nullptr);
  bool hasBack = (back.get() != nullptr);

  // Loop through all the blocks
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      for(int k = 0; k < 16; k++){
        if(!block[i][j][k].visible)
          continue;

        if(k == 0){
          // It is at the front, check if has left exist
          if(hasFront){
            if(front.get()->hasHeight(height) && !front.get()->getBlockChunk(height).getBlockInfo()[i][j][15].visible)
              getBlockChunk(height).addFace(i, j, k, Direction::FRONT);
            else if(!front.get()->hasHeight(height)){
              getBlockChunk(height).addFace(i, j, k, Direction::FRONT);
            }
          } else {
            //getBlockChunk(height).addFace(i, j, k, Direction::BACK);
          }
          if(!block[i][j][k+1].visible){
            getBlockChunk(height).addFace(i, j, k, Direction::BACK);
          }
        } else if(k == 15){
          if(hasBack){
            if(back.get()->hasHeight(height) && !back.get()->getBlockChunk(height).getBlockInfo()[i][j][0].visible)
              getBlockChunk(height).addFace(i, j, k, Direction::BACK);
            else if(!back.get()->hasHeight(height)){
              getBlockChunk(height).addFace(i, j, k, Direction::BACK);
            }
          } else {
            //Do nothing
            //getBlockChunk(height).addFace(i, j, k, Direction::FRONT);
          }
          if(!block[i][j][k-1].visible){
            getBlockChunk(height).addFace(i, j, k, Direction::FRONT);
          }
        } else {
          // check within the block
        if(!block[i][j][k-1].visible){
          getBlockChunk(height).addFace(i, j, k, Direction::FRONT);
          }
          if(!block[i][j][k+1].visible){
            getBlockChunk(height).addFace(i, j, k, Direction::BACK);
          }

        }
      }
    }
  }
}

void HeightChunk::testBlockChunksLeftRight(int height, std::shared_ptr<HeightChunk> left,  std::shared_ptr<HeightChunk>  right){

    BlockChunk& blockChunk = m_chunks[height];
    std::vector<std::vector<std::vector<BlockInfo>>>& block = blockChunk.getBlockInfo();
    bool hasLeft = (left.get() != nullptr);
    bool hasRight = (right.get() != nullptr);

    // Loop through all the blocks
    for(int i = 0; i < 16; i++){
      for(int j = 0; j < 16; j++){
        for(int k = 0; k < 16; k++){
          if(!block[i][j][k].visible)
            continue;

          if(i == 0){
            // It is at the front, check if has left exist
            if(hasLeft){
              if(left.get()->hasHeight(height) && !left.get()->getBlockChunk(height).getBlockInfo()[15][j][k].visible)
                getBlockChunk(height).addFace(i, j, k, Direction::LEFT);
              else if(!left.get()->hasHeight(height))
                getBlockChunk(height).addFace(i, j, k, Direction::LEFT);
            } else {
              //getBlockChunk(height).addFace(i, j, k, Direction::LEFT);
            }
            if(!block[i+1][j][k].visible){
              getBlockChunk(height).addFace(i, j, k, Direction::RIGHT);
            }

          } else if(i == 15){
            if(hasRight){
              if(right.get()->hasHeight(height) && !right.get()->getBlockChunk(height).getBlockInfo()[0][j][k].visible)
                getBlockChunk(height).addFace(i, j, k, Direction::RIGHT);
              else if(!right.get()->hasHeight(height))
                getBlockChunk(height).addFace(i, j, k, Direction::RIGHT);
            } else {
              //getBlockChunk(height).addFace(i, j, k, Direction::RIGHT);
            }
            if(!block[i-1][j][k].visible){
              getBlockChunk(height).addFace(i, j, k, Direction::LEFT);
            }
          } else {
            // check within the block
            if(!block[i-1][j][k].visible){
              getBlockChunk(height).addFace(i, j, k, Direction::LEFT);
            }
            if(!block[i+1][j][k].visible){
              getBlockChunk(height).addFace(i, j, k, Direction::RIGHT);
            }

          }
        }
      }
    }
}

void HeightChunk::updateBlockChunk(int height, std::shared_ptr<HeightChunk> left, std::shared_ptr<HeightChunk> right, std::shared_ptr<HeightChunk> front, std::shared_ptr<HeightChunk> back){

  testBlockChunksFrontBack(height, front, back);
  testBlockChunksLeftRight(height, left, right);
  testBlockChunksTopDown(height);

}

std::vector<std::shared_ptr<ChunkMesh>> HeightChunk::getChunkMesh(){
  std::vector<std::shared_ptr<ChunkMesh>> temp;
  for(int i = 0; i < m_chunks.size(); i++){
    temp.emplace_back(m_chunks[i].getMesh());
  }
  return temp;
}

void HeightChunk::updateHeightChunk(std::shared_ptr<HeightChunk> left, std::shared_ptr<HeightChunk> right, std::shared_ptr<HeightChunk> front, std::shared_ptr<HeightChunk> back){

  m_isProcessing = true;
	for(int i = 0; i < m_chunks.size(); i++){


    updateBlockChunk(i, left, right, front, back);

  }
  m_isMeshReady = true;
  m_isNeedUpdate = false;
  m_isProcessing = false;

}

int HeightChunk::getHeight(){
    return m_chunks.size();
}

bool HeightChunk::hasHeight(int height){
  return (height < (int)m_chunks.size());
}

void HeightChunk::testBlockChunksLeftRight(int cur_height, BlockChunk& bc, Direction dir){
  int currentWidth = 0;
  int currentLength = 0;

  int otherWidth = 0;
  int otherLength = 0;

  bool leftRightFlag = false;

  switch(dir){
    case Direction::LEFT :
      otherWidth = 15;
      leftRightFlag = true;
      break;
    case Direction::RIGHT :
      currentWidth = 15;
      leftRightFlag = true;
      break;
    case Direction::FRONT :
      otherLength = 15;
      break;
    case Direction::BACK :
      currentLength = 15;
      break;
    default: break;
  }
  for(int width = currentWidth; width < 16; width ++){
      for(int length = currentLength; length < 16; length++){
        if(!getBlockChunk(cur_height).getBlockInfo()[width][cur_height][length].visible)
          continue;
        // Either going left right or front back
        if(leftRightFlag){
          if(!bc.getBlockInfo()[otherWidth][cur_height][length].visible ){
            getBlockChunk(cur_height).addFace(width, cur_height, length, dir);
          }
        } else {
          if(!bc.getBlockInfo()[width][cur_height][otherLength].visible){
            getBlockChunk(cur_height).addFace(width, cur_height, length, dir);
          }
        }
      }
  }
}

void HeightChunk::testBlockChunksTopDown(int height){
  BlockChunk& blockChunk = m_chunks[height];
  std::vector<std::vector<std::vector<BlockInfo>>>& block = blockChunk.getBlockInfo();

  // Loop through all the blocks
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      for(int k = 0; k < 16; k++){
        if(!block[i][j][k].visible)
          continue;

        if(j == 0){
          if(height == 0){
              //getBlockChunk(height).addFace(i, 0, k, Direction::DOWN);
          } else {

            if(!getBlockChunk(height-1).getBlockInfo()[i][15][k].visible)
              getBlockChunk(height).addFace(i, 0, k, Direction::DOWN);
          }
          if(!block[i][j+1][k].visible){
            getBlockChunk(height).addFace(i, j, k, Direction::UP);
          }
        } else if(j == 15){
          if(height == m_chunks.size() - 1){
            if(getBlockChunk(height).getBlockInfo()[i][15][k].visible)
              getBlockChunk(height).addFace(i, 15, k, Direction::UP);
          } else {
            if(!getBlockChunk(height+1).getBlockInfo()[i][0][k].visible)
              getBlockChunk(height).addFace(i, 15, k, Direction::UP);
          }
          if(!block[i][j-1][k].visible){
            getBlockChunk(height).addFace(i, j, k, Direction::DOWN);
          }
        } else {
          // check within the block
          if(!block[i][j+1][k].visible){
            getBlockChunk(height).addFace(i, j, k, Direction::UP);
          }
          if(!block[i][j-1][k].visible){
            getBlockChunk(height).addFace(i, j, k, Direction::DOWN);
          }
        }
      }
    }
  }
}

bool HeightChunk::isHeightReady(){
  return m_isHeightReady;
}

bool HeightChunk::isMeshReady(){
  return m_isMeshReady;
}

bool HeightChunk::isNeedUpdate(){
  return m_isNeedUpdate;
}

bool HeightChunk::isProcessing(){
  return m_isProcessing;
}

void HeightChunk::setIsProcessing(bool m_isProcessing){
  this->m_isProcessing = m_isProcessing;
}

void HeightChunk::setIsNeedUpdate(bool m_isNeedUpdate){
  this->m_isNeedUpdate = m_isNeedUpdate;
}
int HeightChunk::getWidth(){
  return m_width;
}

int HeightChunk::getLength(){
  return m_length;
}

void HeightChunk::clearMesh(){
  m_isNeedUpdate = true;
  m_isHeightReady = true;
  m_isMeshReady = false;

  // CAnnot do that, in case if it is still processing
  //m_isProcessing = false;
	for (int i = 0; i < m_chunks.size(); i++) {

    m_chunks[i].clear();
  }
}

int HeightChunk::getInitWidth(){
  return m_initWidth;
}

int HeightChunk::getInitLength(){
  return m_initLength;
}

void HeightChunk::addLeftMesh(std::shared_ptr<HeightChunk> left){
  // This will go through all block chunks height of the
  for(int i = 0; i < m_chunks.size(); i++){
    BlockChunk& blockChunk = m_chunks[i];
    std::vector<std::vector<std::vector<BlockInfo>>>& block = blockChunk.getBlockInfo();
    for(int length = 0; length < 16; length ++){
      for(int height = 0; height < 16; height ++){
        if(!block[0][height][length].visible)
          continue;
        if(left.get()->getHeight() <= i){
          // Add the left side anyway
          getBlockChunk(i).addFace(0, height, length, Direction::LEFT);
        } else {
          std::vector<std::vector<std::vector<BlockInfo>>>& leftBlock = left.get()->getBlockChunk(i).getBlockInfo();
          if(!leftBlock[15][height][length].visible)
            getBlockChunk(i).addFace(0, height, length, Direction::LEFT);
        }
      }
    }
    getBlockChunk(i).rebuildMesh();
  }
}

void HeightChunk::addRightMesh(std::shared_ptr<HeightChunk> right){
  // This will go through all block chunks height of the
  for(int i = 0; i < m_chunks.size(); i++){
    BlockChunk& blockChunk = m_chunks[i];
    std::vector<std::vector<std::vector<BlockInfo>>>& block = blockChunk.getBlockInfo();
    for(int length = 0; length < 16; length ++){
      for(int height = 0; height < 16; height ++){
        if(!block[15][height][length].visible)
          continue;
        if(right.get()->getHeight() <= i){
          getBlockChunk(i).addFace(15, height, length, Direction::RIGHT);
        } else {
          std::vector<std::vector<std::vector<BlockInfo>>>& rightBlock = right.get()->getBlockChunk(i).getBlockInfo();
          if(!rightBlock[0][height][length].visible)
            getBlockChunk(i).addFace(15, height, length, Direction::RIGHT);
        }
      }
    }
    getBlockChunk(i).rebuildMesh();
  }
}

void HeightChunk::addFrontMesh(std::shared_ptr<HeightChunk> front){
  for(int i = 0; i < m_chunks.size(); i++){
    BlockChunk& blockChunk = m_chunks[i];
    std::vector<std::vector<std::vector<BlockInfo>>>& block = blockChunk.getBlockInfo();
    for(int width = 0; width < 16; width ++){
      for(int height = 0; height < 16; height ++){
        if(!block[width][height][0].visible)
          continue;
        if(front.get()->getHeight() <= i){
          getBlockChunk(i).addFace(width, height, 0, Direction::FRONT);
        } else {
          std::vector<std::vector<std::vector<BlockInfo>>>& frontBlock = front.get()->getBlockChunk(i).getBlockInfo();
          if(!frontBlock[width][height][15].visible)
            getBlockChunk(i).addFace(width, height, 0, Direction::FRONT);
        }
      }
    }
	   getBlockChunk(i).rebuildMesh();
  }
}

void HeightChunk::addBackMesh(std::shared_ptr<HeightChunk> back){
  for(int i = 0; i < m_chunks.size(); i++){
    BlockChunk& blockChunk = m_chunks[i];
    std::vector<std::vector<std::vector<BlockInfo>>>& block = blockChunk.getBlockInfo();
    for(int width = 0; width < 16; width ++){
      for(int height = 0; height < 16; height ++){
        if(!block[width][height][15].visible)
          continue;
        if(back.get()->getHeight() <= i){
          getBlockChunk(i).addFace(width, height, 15, Direction::BACK);
        } else {
          std::vector<std::vector<std::vector<BlockInfo>>>& backBlock = back.get()->getBlockChunk(i).getBlockInfo();
          if(!backBlock[width][height][0].visible){
            getBlockChunk(i).addFace(width, height, 15, Direction::BACK);

          }
        }
      }
    }
    getBlockChunk(i).rebuildMesh();
  }
}
