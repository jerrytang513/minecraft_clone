#include "camera.h"
#include <iostream>

Camera::Camera(Vec3D position, Vec3D target, Vec3D worldUp) :
	position{ position }, target{ target }, worldUp{worldUp}{
		direction = (position - target).normalize();
		std::cout << "DIRX" << direction.coord.x << "DIRY" << direction.coord.y << "DIRZ" << direction.coord.z <<  std::endl;
		right = direction.cross(worldUp).normalize();
		std::cout << "rightX" << right.coord.x << "rightY" << right.coord.y << "rightZ" << right.coord.z <<  std::endl;
		up = right.cross(direction).normalize();
		std::cout << "upX" << up.coord.x << "upY" << up.coord.y << "upZ" << up.coord.z <<  std::endl;
	}

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
