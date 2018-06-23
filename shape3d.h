#ifndef SHAPE3D_H_
#define SHAPE3D_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "vec3d.h"
#include "mesh.h"
#include <vector>


class Shape3D {

protected:

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Shape3D();

public:

	std::vector<Vertex> getVertices();
	std::vector<unsigned int> getIndices();
	std::vector<Texture> getTextures();
	Mesh createMesh();

};

#endif
