#ifndef BLOCKCHUNK_H_
#define BLOCKCHUNK_H_

#include "../blockInfo.h"
#include "../../Vec3D.h"
#include "../Renderer/chunkRenderer.h"
#include "../../shader.h"
#include "direction.h"
#include <vector>
#include "../Resource/textureManger.h"

class BlockChunk{

  std::vector<std::vector<std::vector<BlockInfo>>> blocks;

  int initWidth;
  int initLength;
  int initHeight;

  int indiceCount = 0;

  ChunkMesh* mesh;
  bool needUpdate = true;
  std::vector<int> textureIndexes;
  std::vector<Vec2D> texureCoordinates;
  std::vector<Vec3D> vertices;
  std::vector<int> indices;
public:
  BlockChunk();
  // Feed in Block Chunk size of height data, and block chunk will build the coords
  BlockChunk(int width, int height, int length, std::vector<int> heights);

  void setConfig(int width, int height, int length);

  std::vector<std::vector<std::vector<BlockInfo>>> getBlockInfo();
  void addHeight(int width, int height, int length);
  void updateMesh();
  void draw(ChunkRenderer renderer);
  void setUpdate(bool status);
  void addFace(int i, int j, int k, Direction direction);
};
#endif
