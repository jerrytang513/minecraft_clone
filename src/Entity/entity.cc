#include "entity.h"

Entity::Entity(){
  camera = std::make_shared<Camera>(glm::vec3(128.0f, 128.0f, 128.0f));
  position.coord.x = 128.0f;
  position.coord.y = 128.0f;
  position.coord.z = 128.0f;

  backChunkBound = 143;
  leftChunkBound = 127;
  frontChunkBound = 127;
  rightChunkBound = 143;
}

void Entity::updatePosition(Vec3D position){
  this->position = position;
}

Vec3D Entity::getPosition(){
  return position;
}

std::shared_ptr<Camera> Entity::getCamera(){
  return camera;
}

int Entity::getFrontChunkBound(){
  return frontChunkBound;
}

int Entity::getBackChunkBound(){
  return backChunkBound;
}

int Entity::getLeftChunkBound(){
  return leftChunkBound;
}

int Entity::getRightChunkBound(){
  return rightChunkBound;
}

void Entity::updateFrontBackBound(int movement){
  frontChunkBound += movement;
  backChunkBound += movement;
}

void Entity::updateLeftRightBound(int movement){
  leftChunkBound += movement;
  rightChunkBound += movement;
}
