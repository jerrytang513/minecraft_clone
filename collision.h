#ifndef COLLISION_H_
#define COLLISION_H_

#include "vec3d.h"
class CubeCollision;
class Collision {

protected:

	Vec3D centerPos;
	Vec3D xAxis;
	Vec3D yAxis;
	Vec3D zAxis;
	Collision(Vec3D);
	Collision(Vec3D, Vec3D, Vec3D, Vec3D);

public:

	Vec3D getCenterPos();
	void setCenterPos(Vec3D);

	Vec3D getXAxis();
	Vec3D getYAxis();
	Vec3D getZAxis();

	void setXAxis(Vec3D);
	void setYAxis(Vec3D);
	void setZAxis(Vec3D);

	// Test to see if the current object collides with a cube
	virtual bool isCollideWithCube(CubeCollision) = 0;
};


#endif
