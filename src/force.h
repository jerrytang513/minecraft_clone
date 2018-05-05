#ifndef FORCE_H_
#define FORCE_H_

#include "math/vec3d.h"
#include <iostream>

using namespace std;

class Force{

	Vec3D force;

	public:

	Force();
	Vec3D getForce();

	protected:
	void updateForce(Vec3D force);

};

class GravityForce:public Force{

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
