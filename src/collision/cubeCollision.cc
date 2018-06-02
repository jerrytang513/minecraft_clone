#include "cubeCollision.h"
#include <iostream>

CubeCollision::CubeCollision(Vec3D centerPos,float halfWidth,float halfHeight,float halfDepth):
	Collision{centerPos},halfWidth{halfWidth},halfHeight{halfHeight},halfDepth{halfDepth}{}


bool CubeCollision::isCollideWithCube(CubeCollision b){

	Vec3D t = b.centerPos - centerPos;

        float rxx = this->xAxis.dot(b.xAxis).magnitude();
	float rxy = this->xAxis.dot(b.yAxis).magnitude();
	float rxz = this->xAxis.dot(b.zAxis).magnitude();

	float ryx = this->yAxis.dot(b.xAxis).magnitude();
	float ryy = this->yAxis.dot(b.yAxis).magnitude();
	float ryz = this->yAxis.dot(b.zAxis).magnitude();

	float rzx = this->zAxis.dot(b.xAxis).magnitude();
	float rzy = this->zAxis.dot(b.yAxis).magnitude();
	float rzz = this->zAxis.dot(b.zAxis).magnitude();

	// 15 Testing Conditions
	// 6 plane test
	if(t.dot(this->xAxis).magnitude() > (this->halfWidth + b.halfWidth * rxx + b.halfHeight * rxy + b.halfDepth * rxz))
		return false;
	if(t.dot(this->yAxis).magnitude() > (this->halfHeight + b.halfWidth * ryx + b.halfHeight * ryy + b.halfDepth * ryz))
		return false;
	if(t.dot(this->zAxis).magnitude() > (this->halfDepth + b.halfWidth * rzx + b.halfHeight * rzy + b.halfDepth * rzz))
		return false;
	if(t.dot(b.xAxis).magnitude() > (b.halfWidth + this->halfWidth * rxx + this->halfHeight * ryx + this->halfDepth * rzx))
		return false;
	if(t.dot(b.yAxis).magnitude() > (b.halfHeight + this->halfWidth * rxy + this->halfHeight * ryy + this->halfDepth * rzy))
		return false;
	if(t.dot(b.zAxis).magnitude() > (b.halfDepth + this->halfWidth * rxz + this->halfHeight * ryz + this->halfDepth * rzz))
		return false;

	// 9 axis plane test
	if(t.dot(this->xAxis.cross(b.xAxis)).magnitude() > (abs(this->halfHeight * rzx) + abs(this->halfDepth * ryx) + abs(b.halfHeight * rxz) + abs(b.halfDepth * rxy)))
		return false;
	if(t.dot(this->xAxis.cross(b.yAxis)).magnitude() > (abs(this->halfHeight * rzy) + abs(this->halfDepth * ryy) + abs(b.halfWidth * rxz) + abs(b.halfDepth * rxx)))
		return false;
	if(t.dot(this->xAxis.cross(b.zAxis)).magnitude() > (abs(this->halfHeight * rzz) + abs(this->halfDepth * ryz) + abs(b.halfWidth * rxy) + abs(b.halfHeight * rxx)))
		return false;

	if(t.dot(this->yAxis.cross(b.xAxis)).magnitude() > (abs(this->halfWidth * rzx) + abs(this->halfDepth * rxx) + abs(b.halfHeight * ryz) + abs(b.halfDepth * ryy)))
		return false;
	if(t.dot(this->yAxis.cross(b.yAxis)).magnitude() > (abs(this->halfWidth * rzy) + abs(this->halfDepth * rxy) + abs(b.halfWidth * ryz) + abs(b.halfDepth * ryx)))
		return false;
	if(t.dot(this->yAxis.cross(b.zAxis)).magnitude() > (abs(this->halfWidth * rzz) + abs(this->halfDepth * rxz) + abs(b.halfWidth * ryy) + abs(b.halfHeight * ryx)))
		return false;

	if(t.dot(this->zAxis.cross(b.xAxis)).magnitude() > (abs(this->halfWidth * ryx) + abs(this->halfHeight * rxx) + abs(b.halfHeight * rzz) + abs(b.halfDepth * rzy)))
		return false;
	if(t.dot(this->zAxis.cross(b.yAxis)).magnitude() > (abs(this->halfWidth * ryy) + abs(this->halfHeight * rxy) + abs(b.halfWidth * rzz) + abs(b.halfDepth * rzx)))
		return false;
	if(t.dot(this->zAxis.cross(b.zAxis)).magnitude() > (abs(this->halfWidth * ryz) + abs(this->halfHeight * rxz) + abs(b.halfWidth * rzy) + abs(b.halfHeight * rzx)))
		return false;

	return true;
}
