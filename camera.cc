/*
#include "camera.h"
#include "utilities.h"
#include <iostream>

void Camera::processKeyboard(Movement direction, float deltaTime){
	float velocity = SPEED * deltaTime;
	if (direction == Movement::FORWARD)
		position += front * velocity;
		if (direction == Movement::BACKWARD)
		position -= front * velocity;
	if (direction == Movement::RIGHT)
		position += right * velocity;
	if (direction == Movement::LEFT)
		position -= right * velocity;
	if (direction == Movement::UP)
		position += up * velocity;
	if (direction == Movement::DOWN)
		position -= up * velocity;
	update();
}

float Camera::getZoom(){
	return zoom;
}

Vec3D Camera::getFront(){
	return front;
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch){
	xoffset *= SENSITIVITY;
	yoffset *= SENSITIVITY;
	yaw -= xoffset;
	pitch += yoffset;
	if(constrainPitch){
		if(pitch > 89.0f)
			pitch = 89.0f;
		if(pitch < - 89.0f)
			pitch = -89.0f;
	}
	update();
}

void Camera::processMouseScroll(float yoffset){
	if(zoom >= 1.0f && zoom <= 45.0f)
		zoom -= yoffset;
	if(zoom <= 1.0f)
		zoom = 1.0f;
	if(zoom >= 45.0f)
		zoom = 45.0f;
	update();
}

Camera::Camera(Vec3D position, Vec3D target, Vec3D worldUp) :
	position{ position }, target{ target }, worldUp{worldUp}{
		pitch = PITCH;
		yaw = YAW;
		zoom = ZOOM;
		update();
	}

void Camera::update(){
	front.coord.x = cos(toRadians(yaw)) * cos(toRadians(pitch));
	front.coord.y = sin(toRadians(pitch));
	front.coord.z = sin(toRadians(yaw)) * cos(toRadians(pitch));
	front.normalize();
	direction = (front).normalize();
	right = direction.cross(worldUp).normalize();
	up = right.cross(direction).normalize();
}

void Camera::setPosition(Vec3D position) {
	this->position = position;
	update();
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
*/
