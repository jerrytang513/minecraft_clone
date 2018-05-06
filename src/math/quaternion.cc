#include "quaternion.h"
#include <math.h>

#include <iostream>

Quaternion::Quaternion():w{1},x{0},y{0},z{0}{}

Quaternion::Quaternion(double w,double x,double y,double z):w{w},x{x},y{y},z{z}{}

Quaternion::Quaternion(double w,Vec3D vec):w{w},x{vec.x},y{vec.y},z{vec.z}{}

void Quaternion::normalize(){
	
	double norm = sqrt(w * w + x * x + y * y + z * z);
	double normValue = 1 / norm;

	x *= normValue;
	y *= normValue;
	z *= normValue;
	w *= normValue;
}

Quaternion Quaternion::inverse(){

	double norm = sqrt(w * w + x * x + y * y + z * z);
	norm *= norm;
	norm = 1 / norm;

	return Quaternion(w * norm, -1 * x * norm, -1 * y * norm, -1 * z * norm);

}

Quaternion Quaternion::operator*(const Quaternion q){

	double newW = w * q.w - x * q.x - y * q.y - z * q.z;
	double newX = q.x * w + x * q.w + y * q.z - z * q.y;
	double newY = q.y * w + y * q.w + z * q.x - x * q.z;
	double newZ = q.z * w + z * q.w + x * q.y - y * q.x; 

	return Quaternion(newW, newX, newY, newZ);

}

void Quaternion::toUnionNormQuaternion(){

	double radianAngle = w * M_PI / 180;
	normalize();

	w = cos(radianAngle * 0.5);
	x = x * sin(radianAngle * 0.5);
	y = y * sin(radianAngle * 0.5);
       	z = z * sin(radianAngle * 0.5);	

}

Vec3D Quaternion::rotation(double angle, Vec3D axis){

	// p' = qpq^-1
	Vec3D normalizedAxis = axis.normalize();
	
	Quaternion q(angle,normalizedAxis);
	Quaternion p(0,x,y,z);
	Quaternion inverseQ = q.inverse();

	Quaternion rotationVector = q * p * inverseQ;
	
	std::cout << "R" << rotationVector.x << std::endl;

	return Vec3D(rotationVector.x,rotationVector.y,rotationVector.z);

}

