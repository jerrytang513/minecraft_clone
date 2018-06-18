#ifndef CAMERA_H_
#define CAMERA_H_
#include "vec3d.h"


class Camera {
	Vec3D position;
	Vec3D target;
	Vec3D direction;
	Vec3D right;
	Vec3D up;
	Vec3D worldUp;

public:
	Camera(Vec3D position, Vec3D target, Vec3D worldUp);

	void setPosition(Vec3D position);

	Vec3D getPosition();
	Vec3D getDirection();
	Vec3D getRight();
	Vec3D getUp();




};

#endif