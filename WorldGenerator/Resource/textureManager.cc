#include "textureManger.h"

TextureManger::TextureManger(){

}

TextureManager TextureManger::getInstance(){
  if(instance == nullptr){
    instance = new TextureManager();
  } else {
    return instance;
  }
}

void TextureManager::init(){
  textures.emplace_back(Texture("resources/terrain.jpg"));
}

Texture getTexture(int index){
  return textures[index];
}

std::vector<Vec2D> getCoordinates(Vec2D coordinate){
  static const GLfloat TEX_PER_ROW      = 16;
  static const GLfloat INDV_TEX_SIZE    = 1.0f / TEX_PER_ROW;
  static const GLfloat PIXEL_SIZE       = 1.0f / (float)256;

   GLfloat xMin = (coordinate.values[0] * INDV_TEX_SIZE) + 0.5 * PIXEL_SIZE;
   GLfloat yMin = (coordinate.values[1] * INDV_TEX_SIZE) + 0.5 * PIXEL_SIZE;

   GLfloat xMax = (xMin + INDV_TEX_SIZE) - 0.5 * PIXEL_SIZE;
   GLfloat yMax = (yMin + INDV_TEX_SIZE) - 0.5 * PIXEL_SIZE;

   return
   {
       Vec2D(xMin, yMin),
       Vec2D(xMax, yMin),
       Vec2D(xMax, yMax),
       Vec2D(xMin, yMax)
  };
}
