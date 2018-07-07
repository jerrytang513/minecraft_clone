#ifndef CHUNKRENDERER_H_
#define CHUNKRENDERER_H_
#include "../Chunk/blockChunk.h"
#include "../../src/Mesh/chunkMesh.h"
#include "../Resource/TextureManger.h"
#include "../Chunk/chunkManager.h"
#include "../../shader.h"
#include "direction.h"

class chunkRenderer{
  int m_width;
  int m_height;
  int m_length;

  unsigned int shaderID;
public:
  ChunkRenderer(){}
  void setShaderID(unsigned int shaderID);
  void draw(const ChunkMesh& mesh);
};

#endif
