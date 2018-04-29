#ifndef FORCE_H_
#define FORCE_H_

#include "math/vec3d.h"

class Force{

	float force;

	public:

	Force(float force);
	float getForce();

	protected:
	void updateForce(float force);

};

class GravityForce:public Force{

	const float earthGravity = 9.8f;
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
