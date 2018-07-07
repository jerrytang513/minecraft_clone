#include "chunkRenderer.h"


ChunkRenderer::ChunkRenderer(){}

void setShaderID(unsigned int shaderID){
  this->shaderID = shaderID;
}

void ChunkRenderer::draw(const ChunkMesh& mesh){
  Vec3D chunkCoordinate = mesh.getChunkCoordinate();
  unsigned int textureId = mesh.getTextureId();
  unsigned int VAO = mesh.getVAO();
  unsigned int numTraingles = mesh.getNumTriangles();

  glBindVertexArray(VAO);
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(shaderID, "Texture1"), 0);
  glBindTexture(GL_TEXTURE_2D, textureId);
  glm::mat4 model;
  // Need to scale the chunk mesh by 16.
  model = glm::translate(model, glm::vec3(chunkCoordinate.coord.x, chunkCoordinate.coord.y, chunkCoordinate.coord.z));
  shader.setMat4("model", model);
  glDrawElements(GL_TRIANGLES, numTriangles, GL_UNSIGNED_INT, 0);
}
