#include "object.h"

Object::Object():position{Vec3D(0,0,0)},mass{0},inverseMass{0},forces{},acceleration{Vec3D(0,0,0)},velocity{Vec3D(0,0,0)},damping{0}{}

Object::Object(double x,double y, double z):position{Vec3D(x,y,z)},mass{0},inverseMass{0},forces{},acceleration{Vec3D(0,0,0)},velocity{Vec3D(0,0,0)},damping{0}{}

void Object::setMass(double mass){
	this->mass = mass;
	this->inverseMass = 1 / this->mass;
}

void Object::setInverseMass(double inverseMass){
	this->inverseMass = inverseMass;
}

void Object::addForce(Force force){
	this->forces.emplace_back(force);
}

void Object::addContinuousForce(Force force){
	this->continuousForces.emplace_back(force);
}

void Object::clearForce(){
	this->forces.clear();
}

void Object::setPosition(double x, double y, double z){
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
}

void Object::setPosition(Vec3D vec){
	this->position.x = vec.x;
	this->position.y = vec.y;
	this->position.z = vec.z;
}

double Object::getMass(){
	return this->mass;
}

double Object::getInverseMass(){
	return this->inverseMass;
}

Vec3D Object::getPosition(){
	return this->position;
}

void Object::setAcceleration(Vec3D acceleration){
	this->acceleration.x = acceleration.x;
	this->acceleration.y = acceleration.y;
	this->acceleration.z = acceleration.z;
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

void  Object::setDamping(double damping){
	this->damping = damping;
}

double Object::getDamping(){
	return this->damping;
}

std::vector<Force> Object::getForce(){
	return this->forces;
}

void Object::update(double time){
	Vec3D finalForce(0,0,0);
	std::vector<Force> forces = getForce();
	for(std::vector<Force>::iterator it = forces.begin(); it != forces.end(); it++){
		finalForce += (*it).getForce();
	}
	for(std::vector<Force>::iterator it = continuousForces.begin(); it != continuousForces.end(); it++){
		finalForce += (*it).getForce();
	}
		
	this->acceleration += finalForce * this->getInverseMass();
	this->velocity += (this->acceleration * time);	
	this->position += this->velocity * time ;
	// Considering having applied force (continuously supplying the force to the object)
	clearForce();
}

