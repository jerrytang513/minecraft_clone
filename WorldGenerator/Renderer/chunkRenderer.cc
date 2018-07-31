#include "chunkRenderer.h"


ChunkRenderer::ChunkRenderer(){}

void ChunkRenderer::setShader(Shader shader){
  this->shader = shader;
}


void ChunkRenderer::draw(std::vector<std::shared_ptr<ChunkMesh>> mesh){
  if(mesh.size() == 0)
    return;

  std::vector<unsigned int> textureId;
  for(int i = 0; i < mesh.size(); i++){
    if(mesh[i].get() != nullptr){
      textureId = mesh[i].get()->getTextureIds();
      break;
    }
    if(i == mesh.size() - 1)
      return;
  }

  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(shader.ID, "Texture1"), 0);
  glBindTexture(GL_TEXTURE_2D, textureId[0]);
  for(auto it = mesh.begin(); it != mesh.end(); it++){
    if((*it).get() == nullptr || !((*it)).get()->getCanRender())
      continue;
    Vec3D chunkCoordinate = (*it).get()->getChunkCoordinate();
    unsigned int VAO = (*it).get()->getVAO();
    unsigned int numTriangles = (*it).get()->getNumTriangles();
    glBindVertexArray(VAO);
    glm::mat4 model;
    // Need to scale the chunk mesh by 16.
    model = glm::scale(model, glm::vec3(16, 16, 16));
    model = glm::translate(model, glm::vec3(chunkCoordinate.coord.x,chunkCoordinate.coord.y,chunkCoordinate.coord.z));
    shader.setMat4("model", model);
    glDrawElements(GL_TRIANGLES, numTriangles, GL_UNSIGNED_INT, 0);
  }
}
