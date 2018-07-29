#ifndef SRC_ENTITY_ENTITY
#define SRC_ENTITY_ENTITY

#include <memory>

#include "../../camera.h"
#include "../../vec3d.h"

class Entity{

  Vec3D position;
  std::shared_ptr<Camera> camera;
  int frontChunkBound;
  int leftChunkBound;
  int backChunkBound;
  int rightChunkBound;

public:
  Entity();

  void updatePosition(Vec3D position);
  Vec3D getPosition();
  std::shared_ptr<Camera> getCamera();

  int getFrontChunkBound();
  int getBackChunkBound();
  int getLeftChunkBound();
  int getRightChunkBound();

  void updateFrontBackBound(int movement);
  void updateLeftRightBound(int movement);
};

#endif
