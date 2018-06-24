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

BlockMesh Shape3D::createBlockMesh(){
	const Block verticesArr[] = {
		// top
		Block({- 0.5f, 0.5f, 0.5f, 0.0f, 0.0f}),
		Block({0.5f, 0.5f, 0.5f, 1.0f, 0.0f}),
		Block({0.5f, 0.5f, - 0.5f, 1.0f, 1.0f}),
		Block({- 0.5f, 0.5f, - 0.5f, 0.0f, 1.0f}),

		// left
		Block({- 0.5f, - 0.5f, 0.5f, 0.0f, 0.0f}),
		Block({- 0.5f, - 0.5f, - 0.5f, 1.0f, 0.0f}),
		Block({- 0.5f, 0.5f, - 0.5f, 1.0f, 1.0f}),
		Block({- 0.5f, 0.5f, 0.5f, 0.0f, 1.0f}),

		// right
		Block({ 0.5f, - 0.5f, 0.5f, 0.0f, 0.0f}),
		Block({ 0.5f, - 0.5f, - 0.5f, 1.0f, 0.0f}),
		Block({ 0.5f, 0.5f, - 0.5f, 1.0f, 1.0f}),
		Block({ 0.5f, 0.5f, 0.5f, 0.0f, 1.0f}),

		// front
		Block({ - 0.5f, - 0.5f, 0.5f, 0.0f, 0.0f}),
		Block({ 0.5f, - 0.5f, 0.5f, 1.0f, 0.0f}),
		Block({ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f}),
		Block({ - 0.5f, 0.5f, 0.5f, 0.0f, 1.0f}),

		// back
		Block({ - 0.5f, - 0.5f, - 0.5f, 0.0f, 0.0f}),
		Block({ 0.5f, - 0.5f, - 0.5f, 1.0f, 0.0f}),
		Block({ 0.5f, 0.5f, - 0.5f, 1.0f, 1.0f}),
		Block({ - 0.5f, 0.5f, - 0.5f, 0.0f, 1.0f}),

		// bottom
		Block({- 0.5f, -0.5f, 0.5f, 0.0f, 0.0f}),
		Block({0.5f, -0.5f, 0.5f, 1.0f, 0.0f}),
		Block({0.5f, -0.5f, - 0.5f, 1.0f, 1.0f}),
		Block({- 0.5f, -0.5f, -0.5f, 0.0f, 1.0f})
	};
	std::vector<Block> temp (verticesArr, verticesArr + sizeof(verticesArr) / sizeof(verticesArr[0]));
	blockVerticesArr = temp;
	return BlockMesh(blockVerticesArr, indices, textures);

}
