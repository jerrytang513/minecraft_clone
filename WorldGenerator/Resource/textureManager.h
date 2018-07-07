#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <vector>
#include <map>
#include "../../vec2d.h"

// Singleton Class
class TextureManger{

  std::vector<Texture> textures;
  static TextureManger* instance;

  TextureManger* getInstance();
  TextureManager();
  void init();

public:

  Texture getTexture(int index);
  std::vector<Vec2D> getCoordinates(int index, Vec2D coordinate);
};

#endif
