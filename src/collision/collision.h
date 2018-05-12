#ifndef COLLISION_H_
#define COLLISION_H_

#include "../math/vec3d.h"
class CubeCollision;
class Collision{

	protected:

	Collision() = default;

	public:

	// Test to see if the current object collides with a cube
	virtual bool isCollideWithCube(CubeCollision) = 0;
};


#endif
