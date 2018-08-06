#ifndef WORLDGENERATOR_RESOURCE_TEXTUREMANAGER_H_
#define WORLDGENERATOR_RESOURCE_TEXTUREMANAGER_H_

#include <vector>
#include <map>
#include <mutex>

#include "GL/glew.h"

#include "../../vec2d.h"
#include "../../src/Mesh/texture.h"

// Singleton Class
class TextureManager{

  TextureManager();
  static void init();

  bool isInit = false;
  static std::vector<Texture> textures;
  static std::once_flag initInstanceFlag;

public:

  static TextureManager& getInstance();
  Texture getTexture(int index);
  std::vector<Vec2D> getCoordinates(Vec2D coordinate);
};

#endif
