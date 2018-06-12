#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>
#include <vector>
#include <string>
#include "texture.h"

struct vertexAttribVal{
	int counter;
	int size;
	GLenum type;
	bool normalized;
	int stride;
	const void* pointer;

	vertexAttribVal(int counter,int size,GLenum type,bool normalized,int stride,const void* pointer):counter{counter},size{size},type{type},normalized{normalized},stride{stride},pointer{pointer}{}
};

class Mesh{
public:
	Mesh();

	void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void renderMesh();
	void clearMesh();

	// AttribPointer(GLuint index, int size, GLenum type, bool normalized, int stride, const void* pointer)
	// Mesh will take care of the index
	void addVertexAttribPointer(int, GLenum, bool, int, const void*);
	void addTextureAttrib(std::string path, GLenum texture);

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
	std::vector<vertexAttribVal> vertexVals;
	int counter;
	std::vector<Texture> textures;
};

#endif
