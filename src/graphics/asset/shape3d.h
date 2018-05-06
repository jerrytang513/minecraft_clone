#ifndef SHAPE3D_H_
#define SHAPE3D_H_

#include "../../math/vec3d.h"
#include "../../math/quaternion.h"

class Shape3D{

	Vec3D center;
	protected:

	Shape3D(Vec3D vec);

	public:
	
	virtual void draw() = 0;
	virtual void rotate() = 0;	

};

#endif
