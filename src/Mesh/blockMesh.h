#ifndef BLOCKMESH_H
#define BLOCKMESH_H

#include "texture.h"
#include <GL/glew.h>
#include "../../vec3d.h"
#include "../../vec2d.h"
#include "../../shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <initializer_list>

struct Block{
  Vec3D Position;
  Vec2D TexCoords;
  Block(){}
  Block(std::initializer_list<float> temp){
    float data[5];
    std::copy(temp.begin(), temp.end(), data);
    Position = Vec3D(data[0], data[1], data[2]);
    TexCoords = Vec2D(data[3], data[4]);
  }
  Block(std::initializer_list<float> temp, Vec2D texCoords){
    float data[5];
    std::copy(temp.begin(), temp.end(), data);
    Position = Vec3D(data[0], data[1], data[2]);
    TexCoords = texCoords;
  }
  Block(float data[5]){
    Position = Vec3D(data[0], data[1], data[2]);
    TexCoords = Vec2D(data[3], data[4]);
  }
  Block(float data[3], Vec2D texCoords){
    Position = Vec3D(data[0], data[1], data[2]);
    TexCoords = texCoords;
  }

};
// The block has the data order (top, left, right, front, back, bottom)
class BlockMesh{

public:
  std::vector<Block> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  BlockMesh(){}
  BlockMesh(std::vector<Block> vertices, std::vector<unsigned int> indices,  std::vector<Texture> textures){
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    setupMesh();
  }

  std::vector<unsigned int>& getIndices(){
    return indices;
  }

  std::vector<Texture> getTextures(){
    return textures;
  }
  unsigned int getVAO(){
    return VAO;
  }


  void Draw(Shader shader)
  {

      glBindVertexArray(VAO);
      // bind appropriate textures
      glActiveTexture(GL_TEXTURE0); // active proper texture unit before binding
      glUniform1i(glGetUniformLocation(shader.ID, "Texture1"), 0);
      glBindTexture(GL_TEXTURE_2D, textures[0].id);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glBindTexture(GL_TEXTURE_2D,0);
      glBindTexture(GL_TEXTURE_2D, textures[1].id);
      glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, (void*)(sizeof(indices[0]) * 6));
      glBindTexture(GL_TEXTURE_2D,0);
      glBindTexture(GL_TEXTURE_2D, textures[2].id);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(sizeof(indices[0]) * 30));
      // draw mesh
      glBindVertexArray(0);

      // always good practice to set everything back to defaults once configured.
      glActiveTexture(GL_TEXTURE0);
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
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Block), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Block), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Block), (void*)offsetof(Block, TexCoords));

    glBindVertexArray(0);
  }








};



#endif
