#include "blockChunk.h"//TODO
BlockChunk::BlockChunk():blocks{std::vector<std::vector<std::vector<BlockInfo>>>(16, std::vector<std::vector<BlockInfo>>(16,std::vector<BlockInfo>(16,BlockInfo())))}{}
BlockChunk::BlockChunk(int width,  int height, int length, std::vector<int> heights):initWidth{width},initHeight{height},initLength{length},blocks{std::vector<std::vector<std::vector<BlockInfo>>>(16, std::vector<std::vector<BlockInfo>>(16,std::vector<BlockInfo>(16,BlockInfo())))}{}

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

  std:: cout << "SUCCESS" << std::endl;
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
  if(mesh != nullptr)
    delete mesh;
  mesh = new ChunkMesh(vec, indices, textureIndexes, texureCoordinates, initWidth / 16, initHeight / 16, initLength / 16, unsigned int shaderID);
}

void BlockChunk::draw(ChunkRenderer renderer){
  if(needUpdate){

    needUpdate = false;
  }
  Shader shader = renderer.getShader();
  renderer.draw();
}

void BlockChunk::addFace(int i, int j, int k, Direction direction){
  double faceDimension = 1.0 / 16.0;

  std::vector<Vec2D> texCoords;
  TextureManger* instance = TextureManager::getInstance();

  switch(direction){
    case Direction::UP:
      vertices.emplace_back(Vec3D(-0.5f * faceDimension, 0.5f * faceDimension, 0.5f * faceDimension));
      vertices.emplace_back(Vec3D(0.5f * faceDimension, 0.5f * faceDimension, 0.5f * faceDimension));
      vertices.emplace_back(Vec3D(0.5f * faceDimension, 0.5f * faceDimension, -0.5f * faceDimension));
      vertices.emplace_back(Vec3D(-0.5f * faceDimension, 0.5f * faceDimension, -0.5f * faceDimension));
      texCoords = instance->getCoordinates(Vec2D(0,15));
      break;
    case Direction::LEFT:
      vertices.emplace_back(Vec3D(- 0.5f * faceDimension, - 0.5f * faceDimension, - 0.5f * faceDimension));
  		vertices.emplace_back(Vec3D(- 0.5f * faceDimension, - 0.5f * faceDimension, 0.5f * faceDimension));
  		vertices.emplace_back(Vec3D(- 0.5f * faceDimension, 0.5f * faceDimension, 0.5f * faceDimension));
  		vertices.emplace_back(Vec3D(- 0.5f * faceDimension, 0.5f * faceDimension, - 0.5f * faceDimension));
      texCoords = instance->getCoordinates(Vec2D(3,15));
      break;
    case Direction::RIGHT:
      vertices.emplace_back(Vec3D(0.5f * faceDimension, - 0.5f * faceDimension, 0.5f * faceDimension));
      vertices.emplace_back(Vec3D(0.5f * faceDimension, - 0.5f * faceDimension, - 0.5f * faceDimension));
      vertices.emplace_back(Vec3D(0.5f * faceDimension, 0.5f * faceDimension, - 0.5f * faceDimension));
      vertices.emplace_back(Vec3D(0.5f * faceDimension, 0.5f * faceDimension, 0.5f * faceDimension));
      texCoords = instance->getCoordinates(Vec2D(3,15));
      break;
    case Direction::FRONT:
      vertices.emplace_back(Vec3D(- 0.5f * faceDimension, - 0.5f * faceDimension, 0.5f * faceDimension});
      vertices.emplace_back(Vec3D(0.5f * faceDimension, - 0.5f * faceDimension, 0.5f * faceDimension});
      vertices.emplace_back(Vec3D(0.5f * faceDimension, 0.5f * faceDimension, 0.5f * faceDimension});
      vertices.emplace_back(Vec3D(- 0.5f * faceDimension, 0.5f * faceDimension, 0.5f * faceDimension));
      texCoords = instance->getCoordinates(Vec2D(3,15));
      break;
    case Direction::BACK:
      vertices.emplace_back(Vec3D(0.5f * faceDimension, - 0.5f * faceDimension, - 0.5f * faceDimension));
      vertices.emplace_back(Vec3D(- 0.5f * faceDimension, - 0.5f * faceDimension, - 0.5f * faceDimension));
      vertices.emplace_back(Vec3D(- 0.5f * faceDimension, 0.5f * faceDimension, - 0.5f * faceDimension));
      vertices.emplace_back(Vec3D(0.5f * faceDimension, 0.5f * faceDimension, - 0.5f * faceDimension));
      texCoords = instance->getCoordinates(Vec2D(3,15));
      break;
    case Direction::BOTTOM;
      vertices.emplace_back(Vec3D(- 0.5f * faceDimension, -0.5f * faceDimension, 0.5f * faceDimension));
      vertices.emplace_back(Vec3D(0.5f * faceDimension, -0.5f * faceDimension, 0.5f * faceDimension));
      vertices.emplace_back(Vec3D(0.5f * faceDimension, -0.5f * faceDimension, - 0.5f * faceDimension));
      vertices.emplace_back(Vec3D(- 0.5f * faceDimension, -0.5f * faceDimension, -0.5f * faceDimension));
      texCoords = instance->getCoordinates(Vec2D(2,15));
      break;
    default:
      break;
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
}
