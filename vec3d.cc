#include "vec3d.h"

Vec3D::Vec3D(){
	coord.x = 0.0f;
	coord.y = 0.0f;
	coord.z = 0.0f;
}
Vec3D::Vec3D(float x, float y, float z){
	coord.x = x;
	coord.y = y;
	coord.z = z;
}

// Use Norm2 magnitude
float Vec3D::magnitude() {
	return sqrt(coord.x*coord.x + coord.y *coord.y + coord.z * coord.z);
}

Vec3D Vec3D::normalize() {
	float mag = magnitude();
	float normX = coord.x / mag;
	float normY = coord.y / mag;
	float normZ = coord.z / mag;
	return Vec3D(normX, normY, normZ);
}
///
Vec3D operator+(const Vec3D& vec, const float& val) {
	return Vec3D(vec.coord.x + val, vec.coord.y + val, vec.coord.z + val);
}
Vec3D operator-(const Vec3D& vec, const float& val) {
	return Vec3D(vec.coord.x - val, vec.coord.y - val, vec.coord.z - val);
}
Vec3D operator*(const Vec3D& vec, const float& val) {
	return Vec3D(vec.coord.x * val, vec.coord.y * val, vec.coord.z * val);
}
Vec3D operator/(const Vec3D& vec, const float& val) {
	return Vec3D(vec.coord.x / val, vec.coord.y / val, vec.coord.z / val);
}
///
Vec3D operator+(const float& val, const Vec3D& vec) {
	return Vec3D(vec.coord.x + val, vec.coord.y + val, vec.coord.z + val);
}

Vec3D operator-(const float& val, const Vec3D& vec) {
	return Vec3D(val - vec.coord.x , val - vec.coord.y, val - vec.coord.z);
}
Vec3D operator*(const float& val, const Vec3D& vec) {
	return Vec3D(vec.coord.x * val, vec.coord.y * val, vec.coord.z * val);
}
Vec3D operator/(const float& val, const Vec3D& vec) {
	return Vec3D(val / vec.coord.x, val / vec.coord.y, val / vec.coord.z);
}
///

Vec3D operator+(const Vec3D& vec, const Vec3D& other) {
	return Vec3D(other.coord.x + vec.coord.x, other.coord.y + vec.coord.y, other.coord.z + vec.coord.z);
}

Vec3D operator-(const Vec3D& vec, const Vec3D& other) {
	return Vec3D(vec.coord.x - other.coord.x, vec.coord.y - other.coord.y, vec.coord.z - other.coord.z);
}

Vec3D operator*(const Vec3D& vec, const Vec3D& other) {
	return Vec3D(other.coord.x * vec.coord.x, other.coord.y * vec.coord.y, other.coord.z * vec.coord.z);
}

Vec3D operator/(const Vec3D& vec, const Vec3D& other) {
	return Vec3D(vec.coord.x / other.coord.x, vec.coord.y / other.coord.y, vec.coord.z / other.coord.z);
}

void Vec3D::operator+=(const float &val) {
	coord.x += val;
	coord.y += val;
	coord.z += val;
}
void Vec3D::operator+=(const Vec3D& vec) {
	coord.x += vec.coord.x;
	coord.y += vec.coord.y;
	coord.z += vec.coord.z;
}
void Vec3D::operator-=(const float& val) {
	coord.x -= val;
	coord.y -= val;
	coord.z -= val;
}
void Vec3D::operator-=(const Vec3D& vec) {
	coord.x -= vec.coord.x;
	coord.y -= vec.coord.y;
	coord.z -= vec.coord.z;
}
void Vec3D::operator*=(const float& val) {
	coord.x *= val;
	coord.y *= val;
	coord.z *= val;
}
void Vec3D::operator*=(const Vec3D& vec) {
	coord.x *= vec.coord.x;
	coord.y *= vec.coord.y;
	coord.z *= vec.coord.z;
}
void Vec3D::operator/=(const float& val) {
	coord.x /= val;
	coord.y /= val;
	coord.z /= val;
}
void Vec3D::operator/=(const Vec3D& vec) {
	coord.x /= vec.coord.x;
	coord.y /= vec.coord.y;
	coord.z /= vec.coord.z;
}

Vec3D Vec3D::dot(const Vec3D& vec) {
	return Vec3D(coord.x * vec.coord.x, coord.y * vec.coord.y, coord.z * vec.coord.z);
}

Vec3D Vec3D::cross(const Vec3D& vec) {
	return Vec3D(coord.y * vec.coord.z - coord.z * vec.coord.y, coord.z * vec.coord.x - coord.x * vec.coord.z, coord.x * vec.coord.y - coord.y * vec.coord.x);
}
