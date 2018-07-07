#include "textureManager.h"

TextureManager::TextureManager(){

}

TextureManager& TextureManager::getInstance(){
  static TextureManager textureManager;

  if(!textureManager.isInit){
	textureManager.init();
	textureManager.isInit = true;
  }
  return textureManager;
}

void TextureManager::init(){
  textures.emplace_back(Texture("resources/terrain.jpg"));
}

Texture TextureManager::getTexture(int index){
  return textures[index];
}

std::vector<Vec2D> TextureManager::getCoordinates(Vec2D coordinate){
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
