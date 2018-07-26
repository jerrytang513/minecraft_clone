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
  int total_chunks = max_height / 16;
  int left_over = max_height % 16;

  for(int i = 0; i < total_chunks; i++){
    std::vector<int> temp = m_height;
	  std::for_each(temp.begin(), temp.end(), [i](int& val) {
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
    m_chunks.emplace_back(BlockChunk(m_width * 16, i * 16, m_length * 16, temp));
  }
  if(left_over > 0){
    std::vector<int> temp = m_height;
    std::for_each(temp.begin(), temp.end(), [total_chunks](int& val) {
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
    m_chunks.emplace_back(BlockChunk(m_width * 16, total_chunks * 16, m_length * 16, temp));
  }
  m_isHeightReady = true;
}

void HeightChunk::render(){

}

void HeightChunk::generateHeight(){
  NoiseGenerator& ng = NoiseGenerator::getInstance();
//  std::cout << "GenerateHeight for width "  << m_initWidth << " and length " << m_initLength << std::endl;
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
              getBlockChunk(height).addFace(i, j, k, Direction::BACK);
          } else {
            getBlockChunk(height).addFace(i, j, k, Direction::BACK);
          }
          if(!block[i][j][k+1].visible){
            getBlockChunk(height).addFace(i, j, k, Direction::FRONT);
          }
        } else if(k == 15){
          if(hasBack){
            if(back.get()->hasHeight(height) && !back.get()->getBlockChunk(height).getBlockInfo()[i][j][0].visible)
              getBlockChunk(height).addFace(i, j, k, Direction::FRONT);
          } else {
            //Do nothing
            getBlockChunk(height).addFace(i, j, k, Direction::FRONT);
          }
          if(!block[i][j][k-1].visible){
            getBlockChunk(height).addFace(i, j, k, Direction::BACK);
          }
        } else {
          // check within the block
          if(!block[i][j][k-1].visible){
            getBlockChunk(height).addFace(i, j, k, Direction::BACK);
          }
          if(!block[i][j][k+1].visible){
            getBlockChunk(height).addFace(i, j, k, Direction::FRONT);
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
            } else {
              getBlockChunk(height).addFace(i, j, k, Direction::LEFT);
            }
            if(!block[i+1][j][k].visible){
              getBlockChunk(height).addFace(i, j, k, Direction::RIGHT);
            }

          } else if(i == 15){
            if(hasRight){
              if(right.get()->hasHeight(height) && !right.get()->getBlockChunk(height).getBlockInfo()[0][j][k].visible)
                getBlockChunk(height).addFace(i, j, k, Direction::RIGHT);
            } else {
              getBlockChunk(height).addFace(i, j, k, Direction::RIGHT);
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
  return (height < m_chunks.size());
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
          // It is at the front, check if has left exist
          if(height == 0){
              getBlockChunk(height).addFace(i, 0, k, Direction::DOWN);
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

std::vector<ChunkMesh*> HeightChunk::getChunkMesh(){
  std::vector<ChunkMesh*> temp;
  for(int i = 0; i < m_chunks.size(); i++){
    ChunkMesh* chunkMesh = m_chunks[i].getMesh();
    if(chunkMesh != nullptr)
      temp.emplace_back(m_chunks[i].getMesh());
  }
  return temp;
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

void HeightChunk::setIsNeedUpdate(bool m_isNeedUpdate){
  this->m_isNeedUpdate = m_isNeedUpdate;
}
