#include "vec3d.h"

Vec3D::Vec3D():x{0},y{0},z{0},placeholder{0}{}
Vec3D::Vec3D(float x, float y, float z):x{x},y{y},z{z},placeholder{0}{}

glm::vec3 Vec3D::getGLMVec(){
		return glm::vec3(x,y,z);
}

// Use Norm2 magnitude
float Vec3D::magnitude(){
	return sqrt(x*x + y*y + z*z);
}

Vec3D Vec3D::normalize(){
	float mag = magnitude();
	float normX = x / mag;
	float normY = y / mag;
	float normZ = z / mag;
	return Vec3D(normX,normY,normZ);
}

Vec3D Vec3D::operator+(const float& val){
	Vec3D vec(this->x + val, this->y + val, this->z + val);
	return vec;
}
Vec3D Vec3D::operator+(const Vec3D& vec){
	Vec3D new_vec(this->x + vec.x, this->y + vec.y, this->z + vec.z);
	return new_vec;
}
Vec3D Vec3D::operator-(const float& val){
	Vec3D vec(this->x - val, this->y - val, this->z - val);
	return vec;
}
Vec3D Vec3D::operator-(const Vec3D& vec){
	Vec3D new_vec(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	return new_vec;
}
Vec3D Vec3D::operator*(const float& val){
	Vec3D vec(this->x * val, this->y * val, this->z * val);
	return vec;
}
Vec3D Vec3D::operator*(const Vec3D& vec){
	Vec3D new_vec(this->x * vec.x, this->y * vec.y, this->z * vec.z);
	return new_vec;
}
// TODO: ADD Assert for division by 0
Vec3D Vec3D::operator/(const float& val){
	Vec3D vec(this->x / val, this->y / val, this->z / val);
	return vec;
}
Vec3D Vec3D::operator/(const Vec3D& vec){
	Vec3D new_vec(this->x / vec.x, this->y / vec.y, this->z / vec.z);
	return new_vec;
}

void Vec3D::operator+=(const float &val){
	this->x += val;
	this->y += val;
	this->z += val;
}
void Vec3D::operator+=(const Vec3D& vec){
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
}
void Vec3D::operator-=(const float& val){
	this->x -= val;
	this->y -= val;
	this->z -= val;
}
void Vec3D::operator-=(const Vec3D& vec){
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
}
void Vec3D::operator*=(const float& val){
	this->x *= val;
	this->y *= val;
	this->z *= val;
}
void Vec3D::operator*=(const Vec3D& vec){
	this->x *= vec.x;
	this->y *= vec.y;
	this->z *= vec.z;
}
void Vec3D::operator/=(const float& val){
	this->x /= val;
	this->y /= val;
	this->z /= val;
}
void Vec3D::operator/=(const Vec3D& vec){
	this->x /= vec.x;
	this->y /= vec.y;
	this->z /= vec.z;
}

Vec3D Vec3D::dot(const Vec3D& vec){
	return Vec3D(this->x * vec.x,this->y * vec.y, this->z * vec.z);
}

Vec3D Vec3D::cross(const Vec3D& vec){
	return Vec3D(this->y * vec.z - this->z * vec.y, this->z * vec.x - this->x * vec.z, this->x * vec.y - this->y * vec.x);
}
