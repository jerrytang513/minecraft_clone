#include "quaternion.h"


Quaternion::Quaternion():w{1},x{0},y{0},z{0}{}

Quaternion::Quaternion(float w,float x,float y,float z):w{w},x{x},y{y},z{z}{}

Quaternion::Quaternion(float w,Vec3D vec):w{w},x{vec.x},y{vec.y},z{vec.z}{}

void Quaternion::normalize(){

	float norm = sqrt(w * w + x * x + y * y + z * z);
	float normValue = 1 / norm;

	x *= normValue;
	y *= normValue;
	z *= normValue;
	w *= normValue;
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

Mat4 Quaternion::rotationMatrix(float angle, Vec3D axis){
	Mat4 result;
	Vec3D normalizedAxis = axis.normalize();
	Quaternion q(angle,normalizedAxis);
	result.values[0] = 1 - 2 * q.z * q.z - 2 * q.y * q.y;
	result.values[1] = -2 * q.z * q.w + 2 * q.y * q.x;
	result.values[2] = 2 * q.y * q.w + 2 * q.z * q.x;
	result.values[3] = 0;
	result.values[4] = 2 * q.x * q.y + 2 * q.w * q.z;
	result.values[5] = 1 - 2 * q.z * q.z - 2 * q.x * q.x;
	result.values[6] = 2 * q.z * q.y - 2 * q.x * q.w;
	result.values[7] = 0;
	result.values[8] = 2 * q.x * q.z - 2 * q.w * q.y;
	result.values[9] = 2 * q.y * q.z + 2 * q.w * q.x;
	result.values[10] = 1 - 2 * q.y * q.y - 2 * q.x * q.x;
	result.values[11] = 0;
	result.values[12] = 0;
	result.values[13] = 0;
	result.values[14] = 0;
	result.values[15] = 1;
	return result;
}
