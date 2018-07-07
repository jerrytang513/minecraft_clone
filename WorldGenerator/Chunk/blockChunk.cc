#include "blockChunk.h"//TODO
BlockChunk::BlockChunk(){
  std::vector<std::vector<std::vector<BlockInfo>>> temp {std::vector<std::vector<std::vector<BlockInfo>>>(16, std::vector<std::vector<BlockInfo>>(16,std::vector<BlockInfo>(16,BlockInfo())))};
  blocks = temp;
}
BlockChunk::BlockChunk(int width,  int height, int length, std::vector<int> heights):initWidth{width},initHeight{height},initLength{length}{
  std::vector<std::vector<std::vector<BlockInfo>>> temp {std::vector<std::vector<std::vector<BlockInfo>>>(16, std::vector<std::vector<BlockInfo>>(16,std::vector<BlockInfo>(16,BlockInfo())))};
  blocks = temp;
}

std::vector<std::vector<std::vector<BlockInfo>>> BlockChunk::getBlockInfo(){
  return blocks;
}

void BlockChunk::addHeight(int width, int height, int length){
  if(height > 16)
    height = 16;
  for(int i = 0; i < height; i++){
    BlockInfo block;
    block.x = width + initWidth;
    block.y = i + initHeight;
    block.z = length + initLength;
    block.visible = true;
    blocks[width][i][length] = block;
  }
}

void BlockChunk::setConfig(int width, int height, int length){
  initWidth = width;
  initHeight = height;
  initLength = length;
}

void BlockChunk::setUpdate(bool status){
  needUpdate = status;
}

void BlockChunk::updateMesh(){
  std::cout << "C SIZE" << indices.size() << "A SIZE " << vertices.size() << std::endl;
  mesh = new ChunkMesh(vertices, indices, textureIndexes, textureCoordinates, initWidth / 16, initHeight / 16, initLength / 16);
}

void BlockChunk::draw(ChunkRenderer renderer){
  if(needUpdate){
    updateMesh();
    needUpdate = false;
  }
  renderer.draw(*mesh);
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
