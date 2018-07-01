#include "BlockRenderer.h"

BlockRenderer::BlockRenderer(){
  init();
}

void BlockRenderer::init(){
  textures = {
    Texture("resources/blocks/grass_top.png"),
    Texture("resources/blocks/grass_side.png"),
    Texture("resources/blocks/grass_bot.png")
  };
}

std::vector<Texture> BlockRenderer::getTextures(){
    return textures;
}

Texture BlockRenderer::getTexture(int index){
    return textures[index];
}

void BlockRenderer::setShader(Shader shader){
  this->shader = shader;
}

Shader BlockRenderer::getShader(){
  return shader;
}

void BlockRenderer::setSide(int side){
  this->side = side;
}

void BlockRenderer::setTextureIndex(int textureIndex){
  this->textureIndex = textureIndex;
}

void BlockRenderer::draw(){
  glBindVertexArray(VAO);
  // bind appropriate textures
  glActiveTexture(GL_TEXTURE0); // active proper texture unit before binding
  glUniform1i(glGetUniformLocation(shader.ID, "Texture1"), 0);

  glBindTexture(GL_TEXTURE_2D, textures[textureIndex].id);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindTexture(GL_TEXTURE_2D,0);

  // draw mesh
  glBindVertexArray(0);

  // always good practice to set everything back to defaults once configured.
  glActiveTexture(GL_TEXTURE0);
}

void BlockRenderer::setVAO(unsigned int VAO){
  this->VAO = VAO;
}

void BlockRenderer::setIndices(std::vector<unsigned int> indices){
  this->indices = indices;
}
