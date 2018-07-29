#include "player.h"

Player::Player():Entity{}{
}

Vec3D Player::getStartingPosition(){
  return Vec3D(128.0f, 128.0f, 128.0f);
}
