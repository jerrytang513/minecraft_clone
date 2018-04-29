#include "force.h"

Force::Force(float force):force{force}{}

float Force::getForce(){return this->force;}

void Force::updateForce(float force){this->force = force;}

GravityForce::GravityForce(float mass):Force{mass * earthGravity},mass{mass},gravity{earthGravity}{}

GravityForce::GravityForce(float mass, float gravity):Force{mass * gravity},mass{mass},gravity{gravity}{}

float GravityForce::getGravity(){return this->gravity;}

void GravityForce::setGravity(float gravity){
	this->gravity = gravity;
	updateForce(this->mass * this->gravity);
}

float GravityForce::getMass(){return this->mass;}

void GravityForce::setMass(float mass){
	this->mass = mass;
	updateForce(this->mass * this->gravity);
}
