#include "force.h"
#include "math/vec3d.h"

Force::Force(){}
Force::Force(Vec3D force):force{force}{}

Vec3D Force::getForce(){return this->force;}

void Force::updateForce(Vec3D force){this->force = force;}

AppliedForce::AppliedForce(Vec3D force):Force{force}{}

GravityForce::GravityForce(float mass):Force{},mass{mass},gravity{earthGravity}{

	updateForce(Vec3D(0,mass * gravity,0));
}

GravityForce::GravityForce(float mass, float gravity):Force{},mass{mass},gravity{gravity}{
	updateForce(Vec3D(0,mass * gravity,0));
}

float GravityForce::getGravity(){return gravity;}

void GravityForce::setGravity(float gravity){
	this->gravity = gravity;
	updateForce(Vec3D(0,this->mass * this->gravity,0));
}

float GravityForce::getMass(){return this->mass;}

void GravityForce::setMass(float mass){
	this->mass = mass;
	updateForce(Vec3D(0,this->mass * this->gravity,0));
}
