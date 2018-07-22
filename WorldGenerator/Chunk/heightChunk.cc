#include "heightChunk.h"

HeightChunk::HeightChunk(int m_width, int m_height, int m_initWidth, int m_initHeight):
  m_id{m_id},
  m_width{m_width},
  m_length{m_length},
  m_initWidth{m_initWidth},
  m_initLength{m_initLength}
  {
    generateHeight();
    init();
  }

void HeightChunk::init(){
  int total_chunks = max_height / 16;
  int left_over = max_height % 16;

  for(int i = 0; i < total_chunks; i++){
    std::vector<int> tempHeight = height;
    for(auto i = height.begin(); i != height.end(); i ++){

    }
    m_chunks.emplace_back(BlockChunk(m_initWidth, i * 16, m_initLength));
  }
  if(left_over > 0){
    std::vector<int> temp = height;
    std::for_each(temp.begin(), temp.end(), [](int& val){val -= total_chunks * 16});
    m_chunks.emplace_back(BlockChunk(m_initWidth, total_chunks * 16, m_initLength, temp));
  }

}

void HeightChunk::render(){

}

void HeightChunk::generateHeight(){
  NoiseGenerator* ng = NoiseGenerator::getInstance();

  // Generate all the heights, and get the maximum height.
  for(int width = 0; width < 16; width ++ ){
    for(int length = 0; length < 16; length ++ ){
      int new_height = ng.getHeight(width + m_initWidth, length + m_initLength);
      max_height = max_height < new_height ? new_height : max_height;
      height.emplace_back(new_height);
    }
  }
}

void HeightChunk::updateBlockChunk(int m_height, std::shared_ptr<HeightChunk> left, std::shared_ptr<HeightChunk> right, std::shared_ptr<HeightChunk> front, std::shared_ptr<HeightChunk> back){
  // First update the block chunk at the current height with itself. (Not Checking Edge Cases)
  BlockChunk& blockChunk = m_chunks[m_height];
  std::vector<std::vector<std::vector<BlockInfo>>>& block = blockChunk.getBlockInfo();

  for(int width = 1; width <= 14; width++){
    for(int height = 1; height <= 14; height++){
      for(int length = 1; length <= 14; length++){
        if (!block[width][height][length].visible)
          continue;
        if (!block[width - 1][height][length].visible){
            blockChunk.addFace(width, height, length, Direction::LEFT);
        }

        if (!block[width + 1][height][length].visible){
            blockChunk.addFace(width, height, length, Direction::RIGHT);
        }

        if (!block[width][height - 1][length].visible){
            blockChunk.addFace(width, height, length, Direction::DOWN);
        }

        if (!block[width][height + 1][length].visible){
            blockChunk.addFace(width, height, length, Direction::UP);
        }

        if (!block[width][height][length - 1].visible){
            blockChunk.addFace(width, height, length, Direction::BACK);
        }

        if (!block[width][height][length + 1].visible){
            blockChunk.addFace(width, height, length, Direction::FRONT);
        }
      }
    }
  }

  // Second check edge cases at left, right, front, back
  if(left.get() == nullptr || !left.get().hasHeight(height)){
    addHeightFace(Direction::LEFT);
  } else {
    testBlockChunksLeftRight(height, left.get().getBlockChunk(height), Direction::LEFT);
  }
  if(right.get() == nullptr || !right.get().hasHeight(height)){
    addHeightFace(Direction::RIGHT);
  } else {
    testBlockChunksLeftRight(height, right.get().getBlockChunk(height), Direction::RIGHT);
  }
  if(front.get() == nullptr || !front.get().hasHeight(height)){
    addHeightFace(Direction::FRONT);
  } else {
    testBlockChunksLeftRight(height, front.get().getBlockChunk(height), Direction::FRONT);
  }
  if(back.get() == nullptr || !back.get().hasHeight(height)){
    addHeightFace(Direction::BACK);
  } else {
    testBlockChunksLeftRight(height, back.get().getBlockChunk(height), Direction::BACK);
  }

  // Lastly Check the edge cases at top and bottom.
  testBlockChunksTopDown(int height);
}

unsigned int HeightChunk::get_id(){
  return m_id;
}

int HeightChunk::getHeight(){
    return m_chunks.size();
}

bool HeightChunk::hasHeight(int height){
  return (height <= (getHeight() - 1));
}

void HeightChunk::testBlockChunksLeftRight(int height, BlockChunk& bc, Direction dir){
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
    for(int height = 0; height < 16; height++){
      for(int length = currentLength; length < 16; length++){
        if(!getBlockChunk(height).getBlockInfo()[width][height][length].isVisible)
          continue;
        // Either going left right or front back
        if(leftRightFlag){
          if(!bc.getBlockInfo()[otherWidth][height][length].isVisible)
              getBlockChunk(height).addFace(width, height, length, dir);
        } else {
          if(!bc.getBlockInfo()[width][height][otherLength].isVisible)
              getBlockChunk(height).addFace(width, height, length, dir);
        }

      }
    }
  }
}

void HeightChunk::testBlockChunksTopDown(int height){
  // Check if the height is at the top? if yes, add chunk meshes
  if(m_chunks.size() == height + 1){
    for(int length = 0; length < 16; length ++){
      for(int width = 0; width < 16; width ++){
        m_chunks[height].addFace(width, 15, length, Direction::UP);
      }
    }
  } else {
    BlockChunk& other = m_chunks[height + 1];
    // Compare and then add face build mesh.
    for(int length = 0; length < 16; length ++){
      for(int width = 0; width < 16; width ++){
        if(!other.getBlockInfo()[width][0][length].isVisible)
          m_chunks[height].getBlockInfo()[width][15][length].addFace(width, 15, length, Direction::UP);
      }
    }
  }

  // Check if the height is already at the bottom, if yes add all bottom mesh
  if(height == 0){
    for(int length = 0; length < 16; length ++){
      for(int width = 0; width < 16; width ++){
        m_chunks[height].addFace(width, height, length, Direction::DOWN);
      }
    }
  } else {
    for(int length = 0; length < 16; length ++){
      for(int width = 0; width < 16; width ++){
        if(!other.getBlockInfo()[width][15][length].isVisible)
          m_chunks[height].getBlockInfo()[width][0][length].addFace(width, 0, length, Direction::DOWN);
      }
    }
  }
}
