#include "worldSpace.h"
#include <cstdlib>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

WorldSpace::WorldSpace(int width, int length, int height):blockRenderer(BlockRenderer()){
  // TODO Need to write a function to create different types of block
  c.addTexture("resources/blocks/grass_top.png");
  c.addTexture("resources/blocks/grass_side.png");
  c.addTexture("resources/blocks/grass_bot.png");
  block = c.createBlockMesh();

  Cube cTop;
  Cube cBot;
  Cube cFront;
  Cube cBack;
  Cube cLeft;
  Cube cRight;

  // Add the side for the cube
  cTop.addSide(1);
  cBot.addSide(2);
  cSide.addSide(3);

  cTop.setType(0);
  cBot.setType(2);
  cSide.setType(1);

  BlockMesh top = cTop.createSideMesh();
  BlockMesh bot = cBot.createSideMesh();
  BlockMesh side = cSide.createSideMesh();

  std::vector<int> vec = pn.getCoordinates(width, length, 100 * rand(), 4, 2);

  for(int i = 0; i < width; i++){
    for(int j = 0; j < length; j++){
      Coordinate coord;
      coord.x = i;
      coord.y = vec[j * width + i];
      std::cout << coord.y << std::endl;
      coord.z = j;
      Cube c;
      c.addSide(3);
      c.addSide(1);
      c.addSide(2);
      c.addSide(5);
      c.addSide(4);
      c.addSide(6);
      coord.cube = c;
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
    blockRenderer.setShader(shader);

    for(auto sides = it->cube.getVisibleSides().begin(); sides != it->cube.getVisibleSides.end(); it++){
      if(*sides == 1){
        top.draw(blockRenderer);
      } else if (*sides == 2){
        bot.draw(blockRenderer);
      } else {
        side.draw(blockRenderer);
      }
    }

    //block.Draw(shader);
  }

}
