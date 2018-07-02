#ifndef BLOCKRENDERER_H_
#define BLOCKRENDERER_H_

#include "../../src/Mesh/texture.h"
#include "../../shader.h"
#include <vector>
#include "../../shape3d.h"

enum class Type;
class BlockRenderer{
  Shader shader;
  std::vector<Texture> textures;
  int side;
  Type type;
  int textureIndex;
  int VAO;
  BlockMesh mesh;
  std::vector<unsigned int> indices;

  std::vector<int> sides;

  void init();
public:
  BlockRenderer();
  std::vector<Texture> getTextures();
  Texture getTexture(int index);
  void setShader(Shader& shader);
  Shader getShader();
  void setSide(int side);
  void setTextureIndex(int textureIndex);
  void setVAO(unsigned int VAO);
  void setIndices(std::vector<unsigned int>& indices);
  void setBlockMesh(BlockMesh& mesh);
  void renderSides(std::vector<int> sides);
  void draw();
};

#endif
