#include "chunkRenderer.h"


ChunkRenderer::ChunkRenderer(){}

void ChunkRenderer::setShader(Shader shader){
  this->shader = shader;
}

void ChunkRenderer::draw(ChunkMesh mesh){
  Vec3D chunkCoordinate = mesh.getChunkCoordinate();
  std::vector<unsigned int> textureId = mesh.getTextureIds();
  unsigned int VAO = mesh.getVAO();
  unsigned int numTriangles = mesh.getNumTriangles();

  glBindVertexArray(VAO);
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(shader.ID, "Texture1"), 0);
  std::cout << textureId[0] << std::endl;
  glBindTexture(GL_TEXTURE_2D, textureId[0]);
  glm::mat4 model;
  // Need to scale the chunk mesh by 16.
  model = glm::scale(model, glm::vec3(16, 16, 16));
  model = glm::translate(model, glm::vec3(chunkCoordinate.coord.x,chunkCoordinate.coord.y,chunkCoordinate.coord.z));

  shader.setMat4("model", model);
  glDrawElements(GL_TRIANGLES, 10000, GL_UNSIGNED_INT, 0);
}
