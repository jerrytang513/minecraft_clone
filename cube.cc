#include "cube.h"
using namespace std;

void valueAssign(Vec3D* vertices, GLfloat* data) {

}

Cube::Cube(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength) :Shape3D(Vec3D()) {

}

void Cube::draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, data);

	glDrawArrays(GL_QUADS, 0, 24);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void Cube::rotate(GLfloat angle, Vec3D axis) {


}
