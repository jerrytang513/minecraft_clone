#include "eventManager.h"

EventManager::EventManager(){}

// This function will receive the action request and then base on the new location information,
// decide if actions need to be made.
void EventManager::movement(Camera_Movement dir, double deltaTime){
  // Get the current Position of the entity
  Vec3D curPosition = entity.get()->getPosition();

  // Process the event and move the camera
  std::shared_ptr<Camera> camera = entity.get()->getCamera();
  camera.get()->ProcessKeyboard(dir, deltaTime);

  // Get the new position of the camera
  Vec3D newPosition = camera.get()->getPosition();

  // Compute the different
  Vec3D difference = newPosition - curPosition;

  // update the entity to have its new position
  entity.get()->updatePosition(newPosition);

  if(newPosition.coord.x > entity.get()->getRightChunkBound()){

    entity.get()->updateLeftRightBound(16);
    ThreadPool::getInstance(0)->submit([this] {ws.get()->moveRight();});

  } else if(newPosition.coord.x < entity.get()->getLeftChunkBound()){
    entity.get()->updateLeftRightBound(-16);
    ThreadPool::getInstance(0)->submit([this] {ws.get()->moveLeft();});
  }

  if(newPosition.coord.z > entity.get()->getBackChunkBound()){
    entity.get()->updateFrontBackBound(16);
    ThreadPool::getInstance(0)->submit([this] {ws.get()->moveFront();});
  } else if(newPosition.coord.z < entity.get()->getFrontChunkBound()){
    entity.get()->updateFrontBackBound(-16);
    ThreadPool::getInstance(0)->submit([this] {ws.get()->moveBack();});
  }

}

void EventManager::action(WorldSpace& ws, EventID event){
  switch(event){
    case EventID::MOVEFRONT:

    case EventID::MOVEBACK:
    case EventID::MOVELEFT:
    case EventID::MOVERIGHT:
    default:
      break;
  }
}

void EventManager::attachEntity(std::shared_ptr<Entity> entity){
  this->entity = entity;
}


void EventManager::attachWorldSpace(std::shared_ptr<WorldSpace> ws){
  this->ws = ws;
}
