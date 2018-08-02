#ifndef CHUNKMESH_H_
#define CHUNKMESH_H_

#include "texture.h"
#include <GL/glew.h>
#include "../../vec3d.h"
#include "../../vec2d.h"
#include "../../shader.h"
#include "../../WorldGenerator/Resource/textureManager.h"

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <initializer_list>

// The block has the data order (top, left, right, front, back, bottom)
class ChunkMesh{
  std::vector<Vec3D> vertices;
  std::vector<Vec3D> normals;
  std::vector<int> indices;
  std::vector<Vec2D> textureCoords;
  std::vector<int> textureIndexes;
  std::vector<float> data;
  Shader m_shader;
  int chunkX;
  int chunkY;
  int chunkZ;
  unsigned int shaderID;
  bool canRender = false;
public:

  void setCanRender(bool canRender){
    this->canRender = canRender;
  }
  bool getCanRender(){
    return canRender;
  }
  ChunkMesh(){}
  ChunkMesh(std::vector<Vec3D> vertices, std::vector<Vec3D> normals, std::vector<int> indices,  std::vector<int> textureIndexes, std::vector<Vec2D> textureCoords, int chunkX, int chunkY, int chunkZ){
    this->vertices = vertices;
    this->normals = normals;
    this->indices = indices;
    this->textureCoords = textureCoords;
    this->textureIndexes = textureIndexes;
    this->chunkX = chunkX;
    this->chunkY = chunkY;
    this->chunkZ = chunkZ;
    auto texCoordIt = textureCoords.begin();
    auto normalIt = normals.begin();
    int normalCount = 0;
    for(auto it = vertices.begin(); it != vertices.end(); it++){
      data.emplace_back(((Vec3D)(*it)).coord.x);
      data.emplace_back(((Vec3D)(*it)).coord.y);
      data.emplace_back(((Vec3D)(*it)).coord.z);

      data.emplace_back(((Vec3D)(*normalIt)).coord.x);
      data.emplace_back(((Vec3D)(*normalIt)).coord.y);
      data.emplace_back(((Vec3D)(*normalIt)).coord.z);

      data.emplace_back(((Vec2D)(*texCoordIt)).coord.x);
      data.emplace_back(((Vec2D)(*texCoordIt)).coord.y);
      texCoordIt ++;

      if(normalCount < 4){
        normalCount ++;
      } else {
        normalCount = 0;
        normalIt ++;
      }
    }

    if(vertices.size() != 0){
      setupMesh();
    }
  }

  void setShaderID(unsigned int shaderID){
    this->shaderID = shaderID;
  }

  unsigned int getShaderID(){
    return shaderID;
  }

  Vec3D getChunkCoordinate(){
    return Vec3D((float)chunkX, (float)chunkY, (float)chunkZ);
  }

  std::vector<int> getTextureIndexes(){
    return textureIndexes;
  }

  std::vector<unsigned int> getTextureIds(){
    std::vector<unsigned int> textureIds;
    for(auto it = textureIndexes.begin(); it != textureIndexes.end(); it ++){
      textureIds.emplace_back(TextureManager::getInstance().getTexture(*it).id);
    }
    return textureIds;
  }

  unsigned int getVAO(){
    return VAO;
  }

  int getNumTriangles(){
    return indices.size();
  }


  std::vector<int> const getIndices(){
    return indices;
  }

private:
    /*  Render data  */
    unsigned int VAO;
    unsigned int VBO, EBO;

  void setupMesh(){

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.

    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));
    // vertex texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
    canRender = true;

  }

};
#endif
