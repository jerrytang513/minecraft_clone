#include "object.h"
#include <iostream>

Object::Object() :position{ Vec3D(0,0,0) }, mass{ 0 }, inverseMass{ 0 }, forces{}, acceleration{ Vec3D(0,0,0) }, velocity{ Vec3D(0,0,0) }, damping{ 0 } {}

Object::Object(float x, float y, float z) : position{ Vec3D(x,y,z) }, mass{ 0 }, inverseMass{ 0 }, forces{}, acceleration{ Vec3D(0,0,0) }, velocity{ Vec3D(0,0,0) }, damping{ 0 } {}

Object::~Object() {
	delete shape;
	delete collision;
}

void Object::setMass(float mass) {
	this->mass = mass;
	this->inverseMass = 1 / this->mass;
}

void Object::setInverseMass(float inverseMass) {
	this->inverseMass = inverseMass;
}

void Object::addForce(Force force) {
	this->forces.emplace_back(force);
}

void Object::addContinuousForce(Force force) {
	this->continuousForces.emplace_back(force);
}

void Object::clearForce() {
	this->forces.clear();
}

void Object::setPosition(float x, float y, float z) {
	this->position.coord.x = x;
	this->position.coord.y = y;
	this->position.coord.z = z;
}

void Object::setPosition(Vec3D vec) {
	this->position.coord.x = vec.coord.x;
	this->position.coord.y = vec.coord.y;
	this->position.coord.z = vec.coord.z;
}

float Object::getMass() {
	return this->mass;
}

float Object::getInverseMass() {
	return this->inverseMass;
}

Vec3D Object::getPosition() {
	return this->position;
}

void Object::setAcceleration(Vec3D acceleration) {
	this->acceleration.coord.x = acceleration.coord.x;
	this->acceleration.coord.y = acceleration.coord.y;
	this->acceleration.coord.z = acceleration.coord.z;
}

Vec3D Object::getAcceleration() {
	return this->acceleration;
}

void Object::setVelocity(Vec3D velocity) {
	this->velocity = velocity;
}

Vec3D Object::getVelocity() {
	return this->velocity;
}

void  Object::setDamping(float damping) {
	this->damping = damping;
}

float Object::getDamping() {
	return this->damping;
}

std::vector<Force> Object::getForce() {
	return this->forces;
}

void Object::update(float time) {
	Vec3D finalForce(0, 0, 0);
	std::vector<Force> forces = getForce();
	for (std::vector<Force>::iterator it = forces.begin(); it != forces.end(); it++) {
		finalForce += (*it).getForce();
	}
	for (std::vector<Force>::iterator it = continuousForces.begin(); it != continuousForces.end(); it++) {
		finalForce += (*it).getForce();
	}
	this->acceleration += finalForce * this->getInverseMass();
	//std::cout << this->acceleration.x << std::endl;
	this->velocity += (this->acceleration * time);
	this->position += this->velocity * time;
	//std::cout << this->position.x << std::endl;

	// update collision info
	collision->setCenterPos(this->position);
	collision->setXAxis((this->shape)->getXAxis());
	collision->setYAxis((this->shape)->getYAxis());
	collision->setZAxis((this->shape)->getZAxis());

	// Considering having applied force (continuously supplying the force to the object)
	clearForce();
}

Collision* Object::getCollision() {
	return this->collision;
}

void Object::attachCube(float centerX, float centerY, float centerZ, float edgeLength) {
	shape = new Cube(centerX, centerY, centerZ, edgeLength);
	collision = new CubeCollision(Vec3D(centerX, centerY, centerZ), edgeLength / 2, edgeLength / 2, edgeLength / 2);
}

void Object::draw() {
	shape->draw();
}

void Object::rotate(GLfloat angle, Vec3D axis) {
	shape->rotate(angle, axis);
}
