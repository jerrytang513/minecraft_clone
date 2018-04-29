#include "object.h"

Object::Object():position{Vec3D(0,0,0)},mass{0},inverseMass{0},forces{},acceleration{Vec3D(0,0,0)},velocity{Vec3D(0,0,0)},damping{0}{}

Object::Object(float x,float y, float z):position{Vec3D(x,y,z)},mass{0},inverseMass{0},forces{},acceleration{Vec3D(0,0,0)},velocity{Vec3D(0,0,0)},damping{0}{}

void Object::setMass(float mass){
	this->mass = mass;
}

void Object::setInverseMass(float inverseMass){
	this->inverseMass = inverseMass;
}

void Object::addForce(Force force){
	this->forces.emplace_back(force);
}

void Object::clearForce(){
	this->forces.clear();
}

void Object::setPosition(float x, float y, float z){
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
}

void Object::setPosition(Vec3D vec){
	this->position.x = vec.x;
	this->position.y = vec.y;
	this->position.z = vec.z;
}

float Object::getMass(){
	return this->mass;
}

float Object::getInverseMass(){
	return this->inverseMass;
}

Vec3D Object::getPosition(){
	return this->position;
}

void Object::setAcceleration(Vec3D acceleration){
	this->acceleration = acceleration;
}

Vec3D Object::getAcceleration(){
	return this->acceleration;
}

void Object::setVelocity(Vec3D velocity){
	this->velocity = velocity;
}

Vec3D Object::getVelocity(){
	return this->velocity;
}

void  Object::setDamping(float damping){
	this->damping = damping;
}

float Object::getDamping(){
	return this->damping;
}

std::vector<Force> Object::getForce(){
	return this->forces;
}

void Object::newton_integrate(float time){
	Vec3D finalForce;
	std::vector<Force> forces = getForce();
	for(std::vector<Force>::iterator it = forces.begin(); it != forces.end(); it++){
		finalForce += (*it).getForce();
	}
	finalForce *= this->getInverseMass();

	this->position += this->velocity * time + (finalForce + this->acceleration) * time * time * 0.5;
}

