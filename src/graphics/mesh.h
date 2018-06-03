#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>

class Mesh{
public:
	Mesh();

	void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void renderMesh();
	void clearMesh();

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

#endif
