#ifndef CUBECOLLISION_H_
#define CUBECOLLISION_H_

#include "collision.h"


class CubeCollision : public Collision {

	float halfWidth;
	float halfHeight;
	float halfDepth;

public:

	CubeCollision(Vec3D, float, float, float);

	virtual bool isCollideWithCube(CubeCollision) override;

};

#endif
