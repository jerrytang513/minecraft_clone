#include "eventManager.h"

EventManager::EventManager(){}

// This function will receive the action request and then base on the new location information,
// decide if actions need to be made.
void EventManager::movement(Camera_Movement dir, double deltaTime){
  std::cout << "MOVEMNET" << std::endl;
  // Get the current Position of the entity

  // Process the event and move the camera
  std::shared_ptr<Camera> camera = entity.get()->getCamera();

  // Get the new position of the camera
  Vec3D newPosition = camera.get()->getPosition();

  // update the entity to have its new position
  entity.get()->updatePosition(newPosition);

  if(newPosition.coord.x > entity.get()->getRightChunkBound()){

    entity.get()->updateLeftRightBound(16);
    ws.get()->moveRight();

  } else if(newPosition.coord.x < entity.get()->getLeftChunkBound()){
    entity.get()->updateLeftRightBound(-16);
    ws.get()->moveLeft();
  }

  if(newPosition.coord.z > entity.get()->getBackChunkBound()){
    entity.get()->updateFrontBackBound(16);
    ws.get()->moveBack();
  } else if(newPosition.coord.z < entity.get()->getFrontChunkBound()){
    entity.get()->updateFrontBackBound(-16);
    ws.get()->moveFront();
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
