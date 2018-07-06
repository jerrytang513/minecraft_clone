#ifndef CHUNKRENDERER_H_
#define CHUNKRENDERER_H_
#include "../Chunk/blockChunk.h"
#include "../../src/Mesh/chunkMesh.h"


class chunkRenderer{
  std::vector<std::vector<std::vector<BlockChunk>>>& m_chunks;
  int m_width;
  int m_height;
  int m_length;

  bool shouldAddFace()
public:
  ChunkRenderer(){}
  Shader getShader();
  void setShader(Shader& shader);
  ChunkMesh getChunkMesh(BlockChunk chunk);
  void draw(ChunkMesh mesh);
  void generateChunkMesh(int chunkX, int chunkY, int chunkZ);






};

#endif
