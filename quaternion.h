#ifndef QUATERNION_H_
#define QUATERNION_H_
#define _USE_MATH_DEFINES
#include <cmath>
#include "vec3d.h"
#include <math.h>
#include <iostream>

class Quaternion {

public:

	float w;
	float x;
	float y;
	float z;

	Quaternion();
	Quaternion(float w, float x, float y, float z);
	Quaternion(float w, Vec3D vec);
	void normalize();
	Quaternion inverse();
	Quaternion operator*(const Quaternion q);
	void toUnionNormQuaternion();
	Vec3D rotation(float angle, Vec3D axis);
};



#endif
