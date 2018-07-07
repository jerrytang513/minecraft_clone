#ifndef FORCE_H_
#define FORCE_H_

#include "vec3d.h"
#include <iostream>

using namespace std;

class Force {

	Vec3D force;

public:

	Force();
	Force(Vec3D);

	Vec3D getForce();

protected:
	void updateForce(Vec3D force);

};

class AppliedForce :public Force {

public:

	AppliedForce(Vec3D);

};

class GravityForce :public Force {

	const float earthGravity = -9.8f;
	float gravity;
	float mass;

public:

	GravityForce(float mass);
	GravityForce(float mass, float gravity);
	float getGravity();
	void setGravity(float gravity);
	float getMass();
	void setMass(float mass);

};

#endif
