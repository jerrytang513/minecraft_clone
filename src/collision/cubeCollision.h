#ifndef CUBECOLLISION_H_
#define CUBECOLLISION_H_

#include "collision.h"


class CubeCollision: public Collision{

	Vec3D xAxis;
	Vec3D yAxis;
	Vec3D zAxis;
	Vec3D centerPoint;

	double halfWidth;
	double halfHeight;
	double halfDepth;

	public:

	CubeCollision(Vec3D centerPoint,double halfWidth,double halfHeight,double halfDepth);
	
	void setXAxis(Vec3D xAxis);
	void setYAxis(Vec3D yAxis);
	void setZAxis(Vec3D zAxis);

	Vec3D getXAxis();
	Vec3D getYAxis();
	Vec3D getZAxis();

	virtual bool isCollideWithCube(CubeCollision cubeCollision) override;

};

#endif
