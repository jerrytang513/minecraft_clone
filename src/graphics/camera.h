#ifndef CAMERA_H_
#define CAMERA_H_
#include "../math/vec3d.h"


class Camera{
  Vec3D position;
  Vec3D direction;
  Vec3D right;
  Vec3D up;

  Camera();
  Camera(Vec3D position, Vec3D direction, Vec3D right);
  Camera(Vec3D position, Vec3D direction, Vec3D right, Vec3D up);



};

#endif
