#include "BlockRenderer.h"

BlockRenderer::BlockRenderer(){
  init();
}

void BlockRenderer::init(){
  textures = {
  };
}

std::vector<Texture> BlockRenderer::getTextures(){
    return textures;
}

Texture BlockRenderer::getTexture(int index){
    return textures[index];
}

void BlockRenderer::setShader(Shader& shader){
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

void BlockRenderer::draw(std::vector<BlockInfo> displayList){
  textures = mesh.getTextures();
  VAO = mesh.getVAO();
  glBindVertexArray(VAO);
  // bind appropriate textures
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(shader.ID, "Texture1"), 0);
  glBindTexture(GL_TEXTURE_2D, textures[0].id);

  for(auto it = displayList.begin(); it != displayList.end(); it++){

    glm::mat4 model;
    //model = glm::translate(model, glm::vec3(it->x, it->y, it->z)); // translate it down so it's at the center of the scene
    //shader.setMat4("model", model);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

  }

  glActiveTexture(GL_TEXTURE0);
}

void BlockRenderer::setVAO(unsigned int VAO){
  this->VAO = VAO;
}

void BlockRenderer::setIndices(std::vector<unsigned int>& indices){
  this->indices = indices;
}

void BlockRenderer::setBlockMesh(BlockMesh& mesh){
  this->mesh = mesh;
}

void BlockRenderer::renderSides(std::vector<int> sides){
  this->sides = sides;
}
