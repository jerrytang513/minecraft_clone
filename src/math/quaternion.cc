#include "quaternion.h"


Quaternion::Quaternion():w{1},x{0},y{0},z{0}{}

Quaternion::Quaternion(float w,float x,float y,float z):w{w},x{x},y{y},z{z}{}

Quaternion::Quaternion(float w,Vec3D vec):w{w},x{vec.x},y{vec.y},z{vec.z}{}

void Quaternion::normalize(){
	float norm = sqrt(x * x + y * y + z * z);
	float normValue = 1 / norm;
	float alpha = w / 180 * M_PI;
	std::cout << M_PI << std::endl;

	x *= normValue;
	y *= normValue;
	z *= normValue;

	x *= sin(alpha / 2);
	y *= sin(alpha / 2);
	z *= sin(alpha / 2);
	w = cos(alpha / 2);
}

Quaternion Quaternion::inverse(){

	float norm = sqrt(w * w + x * x + y * y + z * z);
	norm *= norm;
	norm = 1 / norm;

	return Quaternion(w * norm, -1 * x * norm, -1 * y * norm, -1 * z * norm);

}

Quaternion Quaternion::operator*(const Quaternion q){

	float newW = w * q.w - x * q.x - y * q.y - z * q.z;
	float newX = q.x * w + x * q.w + y * q.z - z * q.y;
	float newY = q.y * w + y * q.w + z * q.x - x * q.z;
	float newZ = q.z * w + z * q.w + x * q.y - y * q.x;

	return Quaternion(newW, newX, newY, newZ);

}

void Quaternion::toUnionNormQuaternion(){

	float radianAngle = w * M_PI / 180;
	normalize();

	w = cos(radianAngle * 0.5);
	x = x * sin(radianAngle * 0.5);
	y = y * sin(radianAngle * 0.5);
  z = z * sin(radianAngle * 0.5);

}

Vec3D Quaternion::rotation(float angle, Vec3D axis){

	// p' = qpq^-1
	Vec3D normalizedAxis = axis.normalize();

	Quaternion q(angle,normalizedAxis);
	Quaternion p(0,x,y,z);
	Quaternion inverseQ = q.inverse();

	Quaternion rotationVector = q * p * inverseQ;

	//std::cout << "R" << rotationVector.x << std::endl;

	return Vec3D(rotationVector.x,rotationVector.y,rotationVector.z);

}
