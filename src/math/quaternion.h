#ifndef QUATERNION_H_
#define QUATERNION_H_

#include "vec3d.h"

class Quaternion{
	
	public:

	double w;
	double x;
	double y;
	double z;
	
	Quaternion();
	Quaternion(double w,double x,double y,double z);
	Quaternion(double w, Vec3D vec);
	void normalize();
	Quaternion inverse();
	Quaternion operator*(const Quaternion q);
	void toUnionNormQuaternion();
	Vec3D rotation(double angle, Vec3D axis);

};

#endif
