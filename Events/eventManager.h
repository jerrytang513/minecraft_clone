#ifndef EVENTS_EVENTMANAGER_H_
#define EVENTS_EVENTMANAGER_H_

#include "eventId.h"
#include "../src/Entity/entity.h"
#include "../src/utility/threadPool.h"

#include "../WorldGenerator/worldSpace.h"

class EventManager{
  std::shared_ptr<Entity> entity;
  std::shared_ptr<WorldSpace> ws;
  Vec3D curPosition;

  int leftRightCount;
  int frontBackCount;
public:
  EventManager();

  void movement(Camera_Movement dir, double deltaTime);
  void action(WorldSpace& ws, EventID event);
  void attachEntity(std::shared_ptr<Entity> entity);
  void attachWorldSpace(std::shared_ptr<WorldSpace> ws);
};

#endif
