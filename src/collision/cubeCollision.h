#ifndef CUBECOLLISION_H_
#define CUBECOLLISION_H_

#include "collision.h"


class CubeCollision: public Collision{

	double halfWidth;
	double halfHeight;
	double halfDepth;

	public:

	CubeCollision(Vec3D,double,double,double);

	virtual bool isCollideWithCube(CubeCollision) override;

};

#endif
