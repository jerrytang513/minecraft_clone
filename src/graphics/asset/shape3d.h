#ifndef SHAPE3D_H_
#define SHAPE3D_H_

#include "../../math/vec3d.h"
#include "../../math/quaternion.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shape3D{

	Vec3D center;
	protected:

	Shape3D(Vec3D vec);

	public:
	
	virtual void draw() = 0;
	virtual void rotate(GLdouble angle,Vec3D axis) = 0;	

};

#endif
