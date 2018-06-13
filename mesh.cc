#include "mesh.h"

Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
	counter = 0;
}

void Mesh::createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices)
{
	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_DYNAMIC_DRAW);

	for (std::vector<vertexAttribVal>::iterator it = vertexVals.begin(); it != vertexVals.end(); ++it) {
		glVertexAttribPointer(it->counter, it->size, it->type, it->normalized, it->stride, it->pointer);
		glEnableVertexAttribArray(it->counter);
	}
	for (std::vector<Texture>::iterator it = textures.begin(); it != textures.end(); ++it) {
		it->init();
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::addVertexAttribPointer(int size, GLenum type, bool normalized, int stride, const void* pointer) {
	vertexVals.emplace_back(vertexAttribVal(counter++, size, type, normalized, stride, pointer));
}

void Mesh::renderMesh()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	for (std::vector<Texture>::iterator it = textures.begin(); it != textures.end(); ++it) {
		it->render();
	}
}

void Mesh::addTextureAttrib(std::string path, GLenum texture) {
	textures.emplace_back(Texture(path, texture));
}

void Mesh::clearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}


Mesh::~Mesh()
{
	clearMesh();
}
