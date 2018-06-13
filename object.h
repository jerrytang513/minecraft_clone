#ifndef OBJECT_H_
#define OBJECT_H_

#include "vec3d.h"
#include <vector>
#include "force.h"
#include "allShape.h"
#include "collision.h"
#include "cubeCollision.h"

using namespace std;

class Object {

	Vec3D position;
	float mass;
	float inverseMass;
	std::vector<Force> forces;
	std::vector<Force> continuousForces;
	Vec3D acceleration;
	Vec3D velocity;
	Shape3D* shape;
	float damping;
	Collision* collision;

	~Object();

public:

	Object();
	Object(float x, float y, float z);

	void setMass(float mass);
	void setInverseMass(float inverseMass);
	std::vector<Force> getForce();
	void addForce(Force force);
	void addContinuousForce(Force force);
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
	void update(float time);

	void attachCube(float centerX, float centerY, float centerZ, float edgeLength);
	void draw();
	void rotate(GLfloat angle, Vec3D axis);

	Collision* getCollision();

};


#endif
