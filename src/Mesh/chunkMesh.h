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
  std::vector<unsigned int> indices;
  std::vector<Vec2D int> textureCoords;
  std::vector<int> textureIndexes
  std::vector<double> data;
  Shader m_shader;
  int chunkX;
  int chunkY;
  int chunkZ;
  unsigned int shaderID;
public:

  ChunkMesh(){}
  ChunkMesh(std::vector<Vec3D> vertices, std::vector<unsigned int> indices,  std::vector<int> textureIndexes, std::vector<Vec2D> textureCoords, int chunkX, int chunkY, int chunkZ){
    this->vertices = vertices;
    this->indices = indices;
    this->textureCoords = textureCoords;
    this->textureIndexes = textureIndexes;
    this->chunkX = chunkX;
    this->chunkY = chunkY;
    this->chunkZ = chunkZ;

    for(auto it = vertices.begin(), texCoordIt = textureCoords.begin(); it != vertices.end(); it++, texCoordIt ++){
      data.emplace_back(*it->coord.x);
      data.emplace_back(*it->coord.y);
      data.emplace_back(*it->coord.z);
      data.emplace_back(*texCoordIt->coord.x);
      data.emplace_back(*texCoordIt->coord.y);
    }
    setupMesh();
  }

  void setShaderID(unsigned int shaderID){
    this->shaderID = shaderID;
  }

  unsigned int getShaderID(){
    return shaderID;
  }

  Vec3D getChunkCoordinate(){
    return Vec3D(chunkX, chunkY, chunkZ);
  }

  std::map<unsigned int, unsigned int> getTextureIndexes(){
    return textureIndexes;
  }

  std::vector<unsigned int> getTextureIds(){
    TextureManager *tm = TextureManger.getInstance();
    std::vector<unsigned int> textureIds;
    for(auto it = textureIndexes.begin(); it != textureIndexes = end(); it ++){
      textureIds.emplace_back(*it);
    }
    return texturesIds;
  }

  unsigned int getVAO(){
    return VAO;
  }

  int getNumtriangles(){
    return vertices.size() / 3;
  }


  std::vector<unsigned int>& const getIndices(){
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
    glBufferData(GL_ARRAY_BUFFER, data.size(), &data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(double) * 5, (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, sizeof(double) * 5, (void*)3 * sizeof(double));

    glBindVertexArray(0);
  }

};
#endif
