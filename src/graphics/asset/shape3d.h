#ifndef SHAPE3D_H_
#define SHAPE3D_H_

#include "../../math/vec3d.h"
#include "../../math/quaternion.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shape3D{

	protected:

	Vec3D center;
	Vec3D xAxis;
	Vec3D yAxis;
	Vec3D zAxis;
	Shape3D(Vec3D vec);
	Shape3D(Vec3D vec,Vec3D xAxis,Vec3D yAxis,Vec3D zAxis);

	public:
	
	virtual void draw() = 0;
	virtual void rotate(GLdouble angle,Vec3D axis) = 0;	

	Vec3D getXAxis();
        Vec3D getYAxis();
        Vec3D getZAxis();

        void setXAxis(Vec3D);
        void setYAxis(Vec3D);
        void setZAxis(Vec3D);


};

#endif
