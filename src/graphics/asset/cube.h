#ifndef CUBE_H_
#define CUBE_H_

#include "shape3d.h"
#include <iostream>

class Cube : public Shape3D{
	GLfloat halfSideLength;
        Vec3D frontTopLeft;
        Vec3D frontTopRight;
        Vec3D frontBottomRight;
        Vec3D frontBottomLeft;

        Vec3D backTopLeft;
        Vec3D backTopRight;
        Vec3D backBottomRight;
        Vec3D backBottomLeft;

        // left face
        Vec3D leftTopLeft;
        Vec3D leftTopRight;
        Vec3D leftBottomRight;
        Vec3D leftBottomLeft;

        // right face
        Vec3D rightTopLeft;
        Vec3D rightTopRight;
        Vec3D rightBottomRight;
        Vec3D rightBottomLeft;

        // top face
        Vec3D topTopLeft;
        Vec3D topTopRight;
        Vec3D topBottomRight;
        Vec3D topBottomLeft;

        // top face
        Vec3D bottomTopLeft;
        Vec3D bottomTopRight;
        Vec3D bottomBottomRight;
        Vec3D bottomBottomLeft;

	Vec3D vertices[24];
	GLfloat data[72];
	public:

	Cube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
	void draw() override;
	void rotate(GLfloat angle,Vec3D axis) override;

};


#endif