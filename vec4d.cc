#include "Vec4D.h"

Coordinate4D::Coordinate4D(float x, float y, float z, float w):x{x}, y{y}, z{z}, w{w}{};

Vec4D::Vec4D() : coord{Coordinate4D(0.0f, 0.0f, 0.0f, 0.0f)}{}
Vec4D::Vec4D(float x, float y, float z, float w) :coord{Coordinate4D(x,y,z,w)} {}

// Use Norm2 magnitude
float Vec4D::magnitude() {
	return sqrt(coord.x*coord.x + coord.y *coord.y + coord.z * coord.z + coord.w * coord.w);
}

Vec4D Vec4D::normalize() {
	float mag = magnitude();
	float normX = coord.x / mag;
	float normY = coord.y / mag;
	float normZ = coord.z / mag;
	float normW = coord.w / mag;
	return Vec4D(normX, normY, normZ, normW);
}
///
Vec4D operator+(const Vec4D& vec, const float& val) {
	return Vec4D(vec.coord.x + val, vec.coord.y + val, vec.coord.z + val, vec.coord.w + val);
}
Vec4D operator-(const Vec4D& vec, const float& val) {
	return Vec4D(vec.coord.x - val, vec.coord.y - val, vec.coord.z - val, vec.coord.w - val);
}
Vec4D operator*(const Vec4D& vec, const float& val) {
	return Vec4D(vec.coord.x * val, vec.coord.y * val, vec.coord.z * val, vec.coord.w * val);
}
Vec4D operator/(const Vec4D& vec, const float& val) {
	return Vec4D(vec.coord.x / val, vec.coord.y / val, vec.coord.z / val, vec.coord.w / val);
}
///
Vec4D operator+(const float& val, const Vec4D& vec) {
	return Vec4D(vec.coord.x + val, vec.coord.y + val, vec.coord.z + val, vec.coord.w + val);
}

Vec4D operator-(const float& val, const Vec4D& vec) {
	return Vec4D(val - vec.coord.x , val - vec.coord.y, val - vec.coord.z, val - vec.coord.w);
}
Vec4D operator*(const float& val, const Vec4D& vec) {
	return Vec4D(vec.coord.x * val, vec.coord.y * val, vec.coord.z * val, vec.coord.w * val);
}
Vec4D operator/(const float& val, const Vec4D& vec) {
	return Vec4D(val / vec.coord.x, val / vec.coord.y, val / vec.coord.z, val / vec.coord.w);
}
///

Vec4D operator+(const Vec4D& vec, const Vec4D& other) {
	return Vec4D(other.coord.x + vec.coord.x, other.coord.y + vec.coord.y, other.coord.z + vec.coord.z, other.coord.w + vec.coord.w);
}

Vec4D operator-(const Vec4D& vec, const Vec4D& other) {
	return Vec4D(vec.coord.x - other.coord.x, vec.coord.y - other.coord.y, vec.coord.z - other.coord.z, vec.coord.w - other.coord.w);
}

Vec4D operator*(const Vec4D& vec, const Vec4D& other) {
	return Vec4D(other.coord.x * vec.coord.x, other.coord.y * vec.coord.y, other.coord.z * vec.coord.z, other.coord.w * vec.coord.w);
}

Vec4D operator/(const Vec4D& vec, const Vec4D& other) {
	return Vec4D(vec.coord.x / other.coord.x, vec.coord.y / other.coord.y, vec.coord.z / other.coord.z, vec.coord.w / other.coord.w);
}

void Vec4D::operator+=(const float &val) {
	coord.x += val;
	coord.y += val;
	coord.z += val;
	coord.w += val;
}
void Vec4D::operator+=(const Vec4D& vec) {
	coord.x += vec.coord.x;
	coord.y += vec.coord.y;
	coord.z += vec.coord.z;
	coord.w += vec.coord.w;
}
void Vec4D::operator-=(const float& val) {
	coord.x -= val;
	coord.y -= val;
	coord.z -= val;
	coord.w -= val;
}
void Vec4D::operator-=(const Vec4D& vec) {
	coord.x -= vec.coord.x;
	coord.y -= vec.coord.y;
	coord.z -= vec.coord.z;
	coord.w -= vec.coord.w;
}
void Vec4D::operator*=(const float& val) {
	coord.x *= val;
	coord.y *= val;
	coord.z *= val;
	coord.w *= val;
}
void Vec4D::operator*=(const Vec4D& vec) {
	coord.x *= vec.coord.x;
	coord.y *= vec.coord.y;
	coord.z *= vec.coord.z;
	coord.w *= vec.coord.w;
}
void Vec4D::operator/=(const float& val) {
	coord.x /= val;
	coord.y /= val;
	coord.z /= val;
	coord.w /= val;
}
void Vec4D::operator/=(const Vec4D& vec) {
	coord.x /= vec.coord.x;
	coord.y /= vec.coord.y;
	coord.z /= vec.coord.z;
	coord.w /= vec.coord.w;
}

Vec4D Vec4D::dot(const Vec4D& vec) {
	return Vec4D(coord.x * vec.coord.x, coord.y * vec.coord.y, coord.z * vec.coord.z, coord.w * vec.coord.w);
}
