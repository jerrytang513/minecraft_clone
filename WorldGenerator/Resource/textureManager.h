#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <vector>
#include <map>
#include "../../vec2d.h"
#include "GL/glew.h"
#include "../../src/Mesh/texture.h"

// Singleton Class
class TextureManager{

  std::vector<Texture> textures;
  TextureManager();
  void init();
  bool isInit = false;

public:

  static TextureManager& getInstance();
  Texture getTexture(int index);
  std::vector<Vec2D> getCoordinates(Vec2D coordinate);
};

#endif
