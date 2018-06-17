#ifndef CUBE_H_
#define CUBE_H_

#include "shape3d.h"
#include <iostream>

class Cube : public Shape3D {
	GLfloat halfSideLength;


	Vec3D vertices[24];
	GLfloat data[72];
public:

	Cube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
	void draw() override;
	void rotate(GLfloat angle, Vec3D axis) override;

};


#endif
