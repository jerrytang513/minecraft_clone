#include "sun.h"

Sun::Sun():Entity{}{
}

Vec3D Sun::getStartingPosition(){
  return Vec3D(50.0f, 200.0f, 50.0f);
}
