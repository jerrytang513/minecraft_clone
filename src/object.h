#ifndef OBJECT_H_
#define OBJECT_H_

#include "math/vec3d.h"
#include <vector>
#include "force.h"

class Object{

	Vec3D position;
	float mass;
	float inverseMass;
	std::vector<Force> forces;
	Vec3D acceleration;
	Vec3D velocity;
	float damping;

	public:

	Object();
	Object(float x,float y,float z);
	
	void setMass(float mass);
	void setInverseMass(float inverseMass);
	std::vector<Force> getForce();
	void addForce(Force force);
	void clearForce();
	void setPosition(float x, float y, float z);
	void setPosition(Vec3D vec);
	float getMass();
	float getInverseMass();
	Vec3D getPosition();
	void setAcceleration(Vec3D acceleration);
	Vec3D getAcceleration();
	void setVelocity(Vec3D velocity);
	Vec3D getVelocity();
	void setDamping(float damping);
	float getDamping();
	void newton_integrate(float time);
	

};


#endif
