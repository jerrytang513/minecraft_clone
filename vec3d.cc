#include "vec3d.h"

Coordinate::Coordinate(float x, float y, float z):x{x},y{y},z{z}{};

Vec3D::Vec3D() : coord{Coordinate(0.0f,0.0f,0.0f)}{}
Vec3D::Vec3D(float x, float y, float z) :coord{Coordinate(x,y,z)} {}

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

Vec3D Vec3D::operator+(const float& val) {
	Vec3D vec(coord.x + val, coord.y + val, coord.z + val);
	return vec;
}
Vec3D Vec3D::operator+(const Vec3D& vec) {
	Vec3D new_vec(coord.x + vec.coord.x, coord.y + vec.coord.y, coord.z + vec.coord.z);
	return new_vec;
}
Vec3D Vec3D::operator-(const float& val) {
	Vec3D vec(coord.x - val, coord.y - val, coord.z - val);
	return vec;
}
Vec3D Vec3D::operator-(const Vec3D& vec) {
	Vec3D new_vec(coord.x - vec.coord.x, coord.y - vec.coord.y, coord.z - vec.coord.z);
	return new_vec;
}
Vec3D Vec3D::operator*(const float& val) {
	Vec3D vec(coord.x * val, coord.y * val, coord.z * val);
	return vec;
}
Vec3D Vec3D::operator*(const Vec3D& vec) {
	Vec3D new_vec(coord.x * vec.coord.x, coord.y * vec.coord.y, coord.z * vec.coord.z);
	return new_vec;
}
// TODO: ADD Assert for division by 0
Vec3D Vec3D::operator/(const float& val) {
	Vec3D vec(coord.x / val, coord.y / val, coord.z / val);
	return vec;
}
Vec3D Vec3D::operator/(const Vec3D& vec) {
	Vec3D new_vec(coord.x / vec.coord.x, coord.y / vec.coord.y, coord.z / vec.coord.z);
	return new_vec;
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
