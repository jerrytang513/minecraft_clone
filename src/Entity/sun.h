#ifndef SRC_ENTITY_SUN_H_
#define SRC_ENTITY_SUN_H_

#include "entity.h"

class Sun: public Entity{

public:
  Sun();
  Vec3D getStartingPosition();

};

#endif
