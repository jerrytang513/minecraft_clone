#include "blockChunk.h"//TODO
BlockChunk::BlockChunk(){
  std::vector<std::vector<std::vector<BlockInfo>>> temp {std::vector<std::vector<std::vector<BlockInfo>>>(16, std::vector<std::vector<BlockInfo>>(16,std::vector<BlockInfo>(16,BlockInfo())))};
  blocks = temp;
}
BlockChunk::BlockChunk(int width,  int height, int length, std::vector<int> heights):initWidth{width},initHeight{height},initLength{length}{
  std::vector<std::vector<std::vector<BlockInfo>>> temp {std::vector<std::vector<std::vector<BlockInfo>>>(16, std::vector<std::vector<BlockInfo>>(16,std::vector<BlockInfo>(16,BlockInfo())))};
  blocks = temp;
}

std::vector<std::vector<std::vector<BlockInfo>>>& BlockChunk::getBlockInfo(){
  return blocks;
}

void BlockChunk::addHeight(int width, int height, int length){
  if(height > 16)
    height = 16;
  if(height < 0 || height - 1 < 0)
    return;
  for(int i = height - 1; i < height; i++){
std::cout << i << std::endl;
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

void BlockChunk::setUpdate(bool status){
  needUpdate = status;
}

void BlockChunk::updateMesh(){

  mesh = new ChunkMesh(vertices, indices, textureIndexes, textureCoordinates, initWidth / 16, initHeight / 16, initLength / 16);
}

ChunkMesh* BlockChunk::getMesh(){
  if(needUpdate){
    updateMesh();
    needUpdate = false;
  }
  return mesh;
}

void BlockChunk::addFace(int i, int j, int k, Direction direction){
  float faceDimension = 1.0f / 16.0f;

  std::vector<Vec2D> texCoords;
  TextureManager instance = TextureManager::getInstance();

  switch(direction){
    case Direction::UP:
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * i, -0.5f + faceDimension * (j + 1), -0.5f  + faceDimension * (k + 1)));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f + faceDimension * (j + 1), -0.5f + faceDimension * (k + 1)));
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * (i + 1), -0.5f + faceDimension * (j + 1), -0.5f  + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f + faceDimension * (j + 1), -0.5f  + faceDimension * k));
      texCoords = instance.getCoordinates(Vec2D(0,15));
      break;
    case Direction::LEFT:
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f  + faceDimension * j, -0.5f  + faceDimension * k));
  		vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f  + faceDimension * j, -0.5f + faceDimension * (k + 1)));
  		vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f + faceDimension * (j + 1), -0.5f + faceDimension * (k + 1)));
  		vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f + faceDimension * (j + 1), -0.5f  + faceDimension * k));
      texCoords = instance.getCoordinates(Vec2D(3,15));
      break;
    case Direction::RIGHT:
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f  + faceDimension * j, -0.5f + faceDimension * (k + 1)));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f  + faceDimension * j, -0.5f  + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f + faceDimension * (j + 1), -0.5f  + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f + faceDimension * (j + 1), -0.5f + faceDimension * (k + 1)));
      texCoords = instance.getCoordinates(Vec2D(3,15));
      break;
    case Direction::FRONT:
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f  + faceDimension * j, -0.5f + faceDimension * (k + 1)));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f  + faceDimension * j, -0.5f + faceDimension * (k + 1)));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f + faceDimension * (j + 1), -0.5f + faceDimension * (k + 1)));
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f + faceDimension * (j + 1), -0.5f + faceDimension * (k + 1)));
      texCoords = instance.getCoordinates(Vec2D(3,15));
      break;
    case Direction::BACK:
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f  + faceDimension * j, -0.5f  + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f  + faceDimension * j, -0.5f  + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f + faceDimension * (j + 1), -0.5f  + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f + faceDimension * (j + 1), -0.5f  + faceDimension * k));
      texCoords = instance.getCoordinates(Vec2D(3,15));
      break;
	case Direction::DOWN:
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f  + faceDimension * j, -0.5f + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f  + faceDimension * j, -0.5f  + faceDimension * k));
      vertices.emplace_back(Vec3D(-0.5f + faceDimension * (i + 1), -0.5f  + faceDimension * j, -0.5f + faceDimension * (k + 1)));
      vertices.emplace_back(Vec3D(-0.5f  + faceDimension * i, -0.5f  + faceDimension * j, -0.5f  + faceDimension * (k + 1)));
      texCoords = instance.getCoordinates(Vec2D(2,15));
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
