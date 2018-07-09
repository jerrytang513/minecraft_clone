#include "chunkRenderer.h"


ChunkRenderer::ChunkRenderer(){}

void ChunkRenderer::setShader(Shader shader){
  this->shader = shader;
}

void ChunkRenderer::draw(std::vector<ChunkMesh*> mesh){
  //std::cout << mesh.size() << std::endl;
  if(mesh.size() == 0)
    return;

  std::vector<unsigned int> textureId = mesh[0]->getTextureIds();
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(shader.ID, "Texture1"), 0);
  glBindTexture(GL_TEXTURE_2D, textureId[0]);

  for(auto it = mesh.begin(); it != mesh.end(); it++){
    Vec3D chunkCoordinate = (*it)->getChunkCoordinate();
    unsigned int VAO = (*it)->getVAO();
    unsigned int numTriangles = (*it)->getNumTriangles();
    glBindVertexArray(VAO);
    glm::mat4 model;
    // Need to scale the chunk mesh by 16.
    model = glm::scale(model, glm::vec3(16, 16, 16));
    model = glm::translate(model, glm::vec3(chunkCoordinate.coord.x,chunkCoordinate.coord.y,chunkCoordinate.coord.z));
    shader.setMat4("model", model);
    glDrawElements(GL_TRIANGLES, numTriangles, GL_UNSIGNED_INT, 0);
  }



}
