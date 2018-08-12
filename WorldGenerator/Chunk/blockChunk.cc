#include "blockChunk.h"

BlockChunk::BlockChunk(){
  std::vector<std::vector<std::vector<BlockInfo>>> temp {std::vector<std::vector<std::vector<BlockInfo>>>(16, std::vector<std::vector<BlockInfo>>(16,std::vector<BlockInfo>(16,BlockInfo())))};
  blocks = temp;

  for(int i = 0; i < 16; i++){
    std::vector<int> vec;
    for(int j = 0; j < 16; j++){
      vec.emplace_back(0);
    }
    highest.emplace_back(vec);
  }

}

BlockChunk::~BlockChunk(){
}


BlockChunk::BlockChunk(int width,  int height, int length, std::vector<int> heights, std::vector<int> actualHeight):initWidth{width},initHeight{height},initLength{length}, m_hightest{actualHeight}{
  std::vector<std::vector<std::vector<BlockInfo>>> temp {std::vector<std::vector<std::vector<BlockInfo>>>(16, std::vector<std::vector<BlockInfo>>(16,std::vector<BlockInfo>(16,BlockInfo())))};
  blocks = temp;
  /*
  for(int i = 0; i < 16; i++){
    std::vector<int> vec;
    for(int j = 0; j < 16; j++){
      vec.emplace_back(0);
    }
    highest.emplace_back(vec);
  }

  // Set visible
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      addHeight(j, heights[i * 16 + j], i);
    }
  }*/

  TypeGen& typeGen = TypeGen::getInstance();
  typeGen.genType(height, blocks, actualHeight);
}

BlockChunk::BlockChunk(int initWidth,  int initHeight, int initLength):initWidth{initWidth},initHeight{initHeight},initLength{initLength}{
  std::vector<std::vector<std::vector<BlockInfo>>> temp {std::vector<std::vector<std::vector<BlockInfo>>>(16, std::vector<std::vector<BlockInfo>>(16,std::vector<BlockInfo>(16,BlockInfo())))};
  blocks = temp;
  for(int i = 0; i < 16; i++){
    std::vector<int> vec;
    for(int j = 0; j < 16; j++){
      vec.emplace_back(0);
    }
    highest.emplace_back(vec);
  }
  for(int length = 0; length < 16; length ++){
    for(int width = 0; width < 16; width ++){
        addHeight(width, 16, length);
      }
  }
}

std::vector<std::vector<int>>& BlockChunk::getHighest(){
  return highest;
}

std::vector<std::vector<std::vector<BlockInfo>>>& BlockChunk::getBlockInfo(){
  return blocks;
}

void BlockChunk::addHeight(int width, int height, int length){
  if(height > 16)
    height = 16;
  if(height < 1)
    return;
  highest[width][length] = height;
  for(int i = 0; i < height; i++){
    blocks[width][i][length].visible = true;
  }
}

void BlockChunk::setConfig(int width, int height, int length){
  initWidth = width;
  initHeight = height;
  initLength = length;
}

void BlockChunk::setIsActive(bool isActive){
  this->isActive = isActive;
}

bool BlockChunk::getIsActive(){
  return isActive;
}

void BlockChunk::setIsReady(bool isReady){
  this->isReady = isReady;
}

bool BlockChunk::getIsReady(){
  return isReady;
}


void BlockChunk::setUpdate(bool status){
  needUpdate = status;
}

void BlockChunk::updateMesh(){
  if(vertices.size() == 0){
    isReady = false;
  } else {
    isReady = true;
    mesh = std::make_shared<ChunkMesh>(vertices, normals, indices, textureIndexes, textureCoordinates, initWidth / 16, initHeight / 16, initLength / 16);
  }
}

std::shared_ptr<ChunkMesh> BlockChunk::getMesh(){
  if(needUpdate){
    updateMesh();
    needUpdate = false;
  }
  return mesh;
}

void BlockChunk::rebuildMesh(){
  needUpdate = true;
}

void BlockChunk::addFace(int i, int j, int k, Direction direction){

  BlockTextures& bt = BlockTextures::getInstance();
  BlockSideCoords& bsc = bt.getTextureCoordinatesByType(blocks[i][j][k].type);

  float faceDimension = 1.0f / 16.0f;
  std::vector<Vec2D> texCoords;
  switch(direction){
    case Direction::UP:
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * i, -0.5f + faceDimension * (j + 1), -0.5f  + faceDimension * (k + 1)));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f + faceDimension * (j + 1), -0.5f + faceDimension * (k + 1)));
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * (i + 1), -0.5f + faceDimension * (j + 1), -0.5f  + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f + faceDimension * (j + 1), -0.5f  + faceDimension * k));
      normals.emplace_back(Vec3D(0.0f, 1.0f, 0.0f));
      texCoords = bsc.top;
      break;
    case Direction::LEFT:
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f  + faceDimension * j, -0.5f  + faceDimension * k));
  		vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f  + faceDimension * j, -0.5f + faceDimension * (k + 1)));
  		vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f + faceDimension * (j + 1), -0.5f + faceDimension * (k + 1)));
  		vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f + faceDimension * (j + 1), -0.5f  + faceDimension * k));
      texCoords = bsc.side;
      normals.emplace_back(Vec3D(-1.0f, 0.0f, 0.0f));
      break;
    case Direction::RIGHT:
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f  + faceDimension * j, -0.5f + faceDimension * (k + 1)));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f  + faceDimension * j, -0.5f  + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f + faceDimension * (j + 1), -0.5f  + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f + faceDimension * (j + 1), -0.5f + faceDimension * (k + 1)));
      texCoords = bsc.side;
      normals.emplace_back(Vec3D(1.0f, 0.0f, 0.0f));
      break;
    case Direction::FRONT:
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f  + faceDimension * j, -0.5f + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f  + faceDimension * j, -0.5f + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f + faceDimension * (j + 1), -0.5f + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f + faceDimension * (j + 1), -0.5f + faceDimension * k));
      texCoords = bsc.side;
      normals.emplace_back(Vec3D(0.0f, 0.0f, -1.0f));
      break;
    case Direction::BACK:
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f  + faceDimension * j, -0.5f  + faceDimension * (k + 1)));
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f  + faceDimension * j, -0.5f  + faceDimension * (k + 1)));
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f + faceDimension * (j + 1), -0.5f  + faceDimension * (k + 1)));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f + faceDimension * (j + 1), -0.5f  + faceDimension * (k + 1)));
      texCoords = bsc.side;
      normals.emplace_back(Vec3D(0.0f, 0.0f, 1.0f));
      break;
	case Direction::DOWN:
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f  + faceDimension * j, -0.5f + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f  + faceDimension * j, -0.5f  + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f  + faceDimension * j, -0.5f + faceDimension * (k + 1)));
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f  + faceDimension * j, -0.5f  + faceDimension * (k + 1)));
      texCoords = bsc.bottom;
      normals.emplace_back(Vec3D(0.0f, -1.0f, 0.0f));
      break;
    default:
      break;
    }

	  textureCoordinates.insert(textureCoordinates.end(), texCoords.begin(), texCoords.end());
      // Add indice to it.
      indices.emplace_back(indiceCount);
      indices.emplace_back(indiceCount + 1);
      indices.emplace_back(indiceCount + 2);
      indices.emplace_back(indiceCount + 2);
      indices.emplace_back(indiceCount + 3);
      indices.emplace_back(indiceCount);
      indiceCount += 4;
      textureIndexes.emplace_back(0);

}

int BlockChunk::getVerticeCount(){
  return vertices.size();
}

void BlockChunk::clear(){
  needUpdate = true;
}

void BlockChunk::setType(int x, int y, int z, BLOCKTYPE type){
  blocks[x][y][z].type = type;
  blocks[x][y][z].visible = true;
}
