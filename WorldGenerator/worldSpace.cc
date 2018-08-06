#include "worldSpace.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

WorldSpace::WorldSpace(int width, int length, int height){
  chunkManager = new ChunkManager(21, 21);
}

void WorldSpace::draw(Shader shader){
    chunkRenderer.setShader(shader);
    chunkManager->draw(chunkRenderer);
}

void WorldSpace::moveFront(){
  chunkManager->moveFront();
}

void WorldSpace::moveBack(){
  chunkManager->moveBack();
}

void WorldSpace::moveLeft(){
  chunkManager->moveLeft();
}

void WorldSpace::moveRight(){
  chunkManager->moveRight();
}

void WorldSpace::click(){


}

void WorldSpace::moveFront(int num){
  chunkManager->moveFront(num);
}

void WorldSpace::moveBack(int num){
  chunkManager->moveBack(num);
}

void WorldSpace::moveLeft(int num){
  chunkManager->moveLeft(num);
}

void WorldSpace::moveRight(int num){
  chunkManager->moveRight(num);
}
