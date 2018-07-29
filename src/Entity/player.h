#ifndef SRC_ENTITY_PLAYER_H
#define SRC_ENTITY_PLAYER_H

#include "entity.h"

class Player: public Entity{

public:
  Player();
  Vec3D getStartingPosition();

};

#endif
