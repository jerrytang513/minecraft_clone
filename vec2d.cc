#include "vec2d.h"

Vec2D::Vec2D(){
	coord.x = 0.0f;
	coord.y = 0.0f;
}
Vec2D::Vec2D(float x, float y){
	coord.x = x;
	coord.y = y;
}

// Use Norm2 magnitude
float Vec2D::magnitude() {
	return sqrt(coord.x*coord.x + coord.y *coord.y);
}

Vec2D Vec2D::normalize() {
	float mag = magnitude();
	float normX = coord.x / mag;
	float normY = coord.y / mag;
	return Vec2D(normX, normY);
}
///
Vec2D operator+(const Vec2D& vec, const float& val) {
	return Vec2D(vec.coord.x + val, vec.coord.y + val);
}
Vec2D operator-(const Vec2D& vec, const float& val) {
	return Vec2D(vec.coord.x - val, vec.coord.y - val);
}
Vec2D operator*(const Vec2D& vec, const float& val) {
	return Vec2D(vec.coord.x * val, vec.coord.y * val);
}
Vec2D operator/(const Vec2D& vec, const float& val) {
	return Vec2D(vec.coord.x / val, vec.coord.y / val);
}
///
Vec2D operator+(const float& val, const Vec2D& vec) {
	return Vec2D(vec.coord.x + val, vec.coord.y + val);
}

Vec2D operator-(const float& val, const Vec2D& vec) {
	return Vec2D(val - vec.coord.x , val - vec.coord.y);
}
Vec2D operator*(const float& val, const Vec2D& vec) {
	return Vec2D(vec.coord.x * val, vec.coord.y * val);
}
Vec2D operator/(const float& val, const Vec2D& vec) {
	return Vec2D(val / vec.coord.x, val / vec.coord.y);
}
///

Vec2D operator+(const Vec2D& vec, const Vec2D& other) {
	return Vec2D(other.coord.x + vec.coord.x, other.coord.y + vec.coord.y);
}

Vec2D operator-(const Vec2D& vec, const Vec2D& other) {
	return Vec2D(vec.coord.x - other.coord.x, vec.coord.y - other.coord.y);
}

Vec2D operator*(const Vec2D& vec, const Vec2D& other) {
	return Vec2D(other.coord.x * vec.coord.x, other.coord.y * vec.coord.y);
}

Vec2D operator/(const Vec2D& vec, const Vec2D& other) {
	return Vec2D(vec.coord.x / other.coord.x, vec.coord.y / other.coord.y);
}

void Vec2D::operator+=(const float &val) {
	coord.x += val;
	coord.y += val;
}
void Vec2D::operator+=(const Vec2D& vec) {
	coord.x += vec.coord.x;
	coord.y += vec.coord.y;
}
void Vec2D::operator-=(const float& val) {
	coord.x -= val;
	coord.y -= val;
}
void Vec2D::operator-=(const Vec2D& vec) {
	coord.x -= vec.coord.x;
	coord.y -= vec.coord.y;
}
void Vec2D::operator*=(const float& val) {
	coord.x *= val;
	coord.y *= val;
}
void Vec2D::operator*=(const Vec2D& vec) {
	coord.x *= vec.coord.x;
	coord.y *= vec.coord.y;
}
void Vec2D::operator/=(const float& val) {
	coord.x /= val;
	coord.y /= val;
}
void Vec2D::operator/=(const Vec2D& vec) {
	coord.x /= vec.coord.x;
	coord.y /= vec.coord.y;
}

Vec2D Vec2D::dot(const Vec2D& vec) {
	return Vec2D(coord.x * vec.coord.x, coord.y * vec.coord.y);
}
