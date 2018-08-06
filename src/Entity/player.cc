#include "player.h"

Player::Player():Entity{}{
}

Vec3D Player::getStartingPosition(){
  return Vec3D(168.0f, 128.0f, 168.0f);
}
