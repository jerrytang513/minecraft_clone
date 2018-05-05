#include "force.h"
#include "math/vec3d.h"

Force::Force(){}

Vec3D Force::getForce(){return this->force;}

void Force::updateForce(Vec3D force){this->force = force;}

GravityForce::GravityForce(double mass):Force{},mass{mass},gravity{earthGravity}{
	
	updateForce(Vec3D(0,mass * gravity,0));
}

GravityForce::GravityForce(double mass, double gravity):Force{},mass{mass},gravity{gravity}{
	updateForce(Vec3D(0,mass * gravity,0));
}

double GravityForce::getGravity(){return gravity;}

void GravityForce::setGravity(double gravity){
	this->gravity = gravity;
	updateForce(Vec3D(0,this->mass * this->gravity,0));
}

double GravityForce::getMass(){return this->mass;}

void GravityForce::setMass(double mass){
	this->mass = mass;
	updateForce(Vec3D(0,this->mass * this->gravity,0));
}
