#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "vec3d.h"
#include <math.h>
#include "mat4.h"
#include <iostream>

class Quaternion{

	public:

	float w;
	float x;
	float y;
	float z;

	Quaternion();
	Quaternion(float w,float x,float y,float z);
	Quaternion(float w, Vec3D vec);
	void normalize();
	Quaternion inverse();
	Quaternion operator*(const Quaternion q);
	void toUnionNormQuaternion();
	Vec3D rotation(float angle, Vec3D axis);
	Mat4 rotationMatrix(float angle, Vec3D axis);

};



#endif
