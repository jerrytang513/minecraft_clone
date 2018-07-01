#include "shape3d.h"

Shape3D::Shape3D(){}

std::vector<Vertex> Shape3D::getVertices(){
	return vertices;
}

std::vector<unsigned int> Shape3D::getIndices(){
	return indices;
}

std::vector<Texture> Shape3D::getTextures(){
	return textures;
}

Mesh Shape3D::createMesh(){
  return Mesh(vertices, indices, textures);
}

void Shape3D::addTexture(const char *path){
	Texture texture(path);
	texture.path = path;
	textures.emplace_back(texture);
}
