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

	const double earthGravity = -9.8;
	double gravity;
	double mass;

public:

	GravityForce(double mass);
	GravityForce(double mass, double gravity);
	double getGravity();
	void setGravity(double gravity);
	double getMass();
	void setMass(double mass);

};

#endif
