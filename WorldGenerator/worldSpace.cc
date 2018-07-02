#include "worldSpace.h"
#include <cstdlib>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

WorldSpace::WorldSpace(int width, int length, int height):blockRenderer(BlockRenderer()){

  std::vector<int> vec = pn.getCoordinates(width, length,  rand(), 4, 2);
  mesh = c.createBlockMesh();

  for(int i = 0; i < width; i++){
    for(int j = 0; j < length; j++){
      Coordinate coord;
      coord.x = i;
      coord.y = vec[j * width + i];
      std::cout << coord.y << std::endl;
      coord.z = j;
      coordinates.emplace_back(coord);
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
    blockRenderer.setBlockMesh(mesh);
    blockRenderer.draw();
  }

}
