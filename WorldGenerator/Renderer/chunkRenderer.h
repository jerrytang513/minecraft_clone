#ifndef CHUNKRENDERER_H_
#define CHUNKRENDERER_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../src/Mesh/chunkMesh.h"
#include "../../shader.h"
#include "direction.h"

class ChunkRenderer{
  int m_width;
  int m_height;
  int m_length;

  Shader shader;
public:
  ChunkRenderer();
  void setShader(Shader shader);
  void draw(const ChunkMesh mesh);
};

#endif
