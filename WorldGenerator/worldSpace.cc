#include "worldSpace.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

WorldSpace::WorldSpace(int width, int length, int height){
  chunkManager = new ChunkManager(width / 16, length / 16);
}

void WorldSpace::draw(Shader shader){
    chunkRenderer.setShader(shader);
    chunkManager->draw(chunkRenderer);
}

void WorldSpace::moveFront(){
  chunkManager->moveFront();
}

void WorldSpace::moveBack(){

}

void WorldSpace::moveLeft(){

}

void WorldSpace::moveRight(){

}

void WorldSpace::click(){
  std::cout << "This is only for testing" << std::endl;
  moveFront();
}
