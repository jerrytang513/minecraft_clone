#include "camera.h"

Camera::Camera(Vec3D position, Vec3D target, Vec3D right) :
	position{ position }, target{ target }, direction{ (position - target).normalize() }
	, right{ right }, up{ direction.cross(right) } {}

void Camera::setPosition(Vec3D position) {
	this->position = position;
}

Vec3D Camera::getPosition() {
	return this->position;
}

Vec3D Camera::getDirection() {
	return this->direction;
}

Vec3D Camera::getRight() {
	return this->right;
}

Vec3D Camera::getUp() {
	return this->up;
}
