#include "vec4d.h"

Vec4D::Vec4D() = default;
Vec4D::Vec4D(float x, float y, float z, float t) :x{ x }, y{ y }, z{ z }, t{ t } {}

// Use Norm2 magnitude
float Vec4D::magnitude() {
	return sqrt(x*x + y * y + z * z + t * t);
}

Vec4D Vec4D::normalize() {
	float mag = magnitude();
	float normX = x / mag;
	float normY = y / mag;
	float normZ = z / mag;
	float normT = t / mag;
	return Vec4D(normX, normY, normZ, normT);
}

Vec4D Vec4D::operator+(const float& val) {
	Vec4D vec(this->x + val, this->y + val, this->z + val, this->t + val);
	return vec;
}
Vec4D Vec4D::operator+(const Vec4D& vec) {
	Vec4D new_vec(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->t + vec.t);
	return new_vec;
}
Vec4D Vec4D::operator-(const float& val) {
	Vec4D vec(this->x - val, this->y - val, this->z - val, this->t - val);
	return vec;
}
Vec4D Vec4D::operator-(const Vec4D& vec) {
	Vec4D new_vec(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->t - vec.t);
	return new_vec;
}
Vec4D Vec4D::operator*(const float& val) {
	Vec4D vec(this->x * val, this->y * val, this->z * val, this->t * val);
	return vec;
}
Vec4D Vec4D::operator*(const Vec4D& vec) {
	Vec4D new_vec(this->x * vec.x, this->y * vec.y, this->z * vec.z, this->t * vec.t);
	return new_vec;
}
// TODO: ADD Assert for division by 0
Vec4D Vec4D::operator/(const float& val) {
	Vec4D vec(this->x / val, this->y / val, this->z / val, this->t / val);
	return vec;
}
Vec4D Vec4D::operator/(const Vec4D& vec) {
	Vec4D new_vec(this->x / vec.x, this->y / vec.y, this->z / vec.z, this->t / vec.t);
	return new_vec;
}

void Vec4D::operator+=(const float &val) {
	this->x += val;
	this->y += val;
	this->z += val;
	this->t += val;
}
void Vec4D::operator+=(const Vec4D& vec) {
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	this->t += vec.t;
}
void Vec4D::operator-=(const float& val) {
	this->x -= val;
	this->y -= val;
	this->z -= val;
	this->t -= val;
}
void Vec4D::operator-=(const Vec4D& vec) {
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	this->t -= vec.t;
}
void Vec4D::operator*=(const float& val) {
	this->x *= val;
	this->y *= val;
	this->z *= val;
	this->t *= val;
}
void Vec4D::operator*=(const Vec4D& vec) {
	this->x *= vec.x;
	this->y *= vec.y;
	this->z *= vec.z;
	this->t *= vec.t;
}
void Vec4D::operator/=(const float& val) {
	this->x /= val;
	this->y /= val;
	this->z /= val;
	this->t /= val;
}
void Vec4D::operator/=(const Vec4D& vec) {
	this->x /= vec.x;
	this->y /= vec.y;
	this->z /= vec.z;
	this->t /= vec.t;
}

Vec4D Vec4D::dot(const Vec4D& vec) {
	return Vec4D(this->x * vec.x, this->y * vec.y, this->z * vec.z, this->t * vec.t);
}
