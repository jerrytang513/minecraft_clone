#include "worldSpace.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void WorldSpace::generateHeight(int width, int height, int length){
  for(int i = 0; i < height; i++){
    Coordinate coord;
    coord.x = width;
    coord.y = i;
    coord.z = length;
    coordinates.emplace_back(coord);
  }
}

WorldSpace::WorldSpace(int width, int height, int length){
  // TODO Need to write a function to create different types of block
  c.addTexture("resources/blocks/grass_top.png");
  c.addTexture("resources/blocks/grass_side.png");
  c.addTexture("resources/blocks/grass_bot.png");
  block = c.createBlockMesh();
  for(int i = 0; i < width; i++){
    for(int j = 0; j < length; j++){
      int n = 20 * pn.noise(i,j,0.8);
      generateHeight(i, n, j);
    }
  }
}

std::vector<Coordinate> WorldSpace::getCoordinates(){
  return coordinates;
}

void WorldSpace::draw(Shader shader){
  for(auto it = coordinates.begin(); it != coordinates.end(); it++){
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(it->x, it->y, it->z)); // translate it down so it's at the center of the scene
    shader.setMat4("model", model);
    block.Draw(shader);
  }

}
