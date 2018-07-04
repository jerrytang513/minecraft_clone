#include "cube.h"

Cube::Cube():Shape3D(){

}

BlockMesh Cube::createBlockMesh(){
	std::vector<Texture> textures = {
			Texture("resources/terrain.jpg"),
	};

	auto top = textures[0].getCoordinates(Vec2D(0,15));
	auto bot = textures[0].getCoordinates(Vec2D(2,15));
	auto side = textures[0].getCoordinates(Vec2D(3,15));

	verticesArray = {

		// top
		Block({- 0.5f, 0.5f, 0.5f},top[0]),
		Block({0.5f, 0.5f, 0.5f},top[1]),
		Block({0.5f, 0.5f, - 0.5f},top[2]),
		Block({- 0.5f, 0.5f, - 0.5f},top[3]),
		// left
		Block({- 0.5f, - 0.5f, - 0.5f},side[0]),
		Block({- 0.5f, - 0.5f, 0.5f},side[1]),
		Block({- 0.5f, 0.5f, 0.5f},side[2]),
		Block({- 0.5f, 0.5f, - 0.5f},side[3]),
		// right
		Block({ 0.5f, - 0.5f, 0.5f},side[0]),
		Block({ 0.5f, - 0.5f, - 0.5f},side[1]),
		Block({ 0.5f, 0.5f, - 0.5f},side[2]),
		Block({ 0.5f, 0.5f, 0.5f},side[3]),
		// front
		Block({ - 0.5f, - 0.5f, 0.5f},side[0]),
		Block({ 0.5f, - 0.5f, 0.5f},side[1]),
		Block({ 0.5f, 0.5f, 0.5f},side[2]),
		Block({ - 0.5f, 0.5f, 0.5f},side[3]),
		// back
		Block({ 0.5f, - 0.5f, - 0.5f},side[0]),
		Block({ - 0.5f, - 0.5f, - 0.5f},side[1]),
		Block({ - 0.5f, 0.5f, - 0.5f},side[2]),
		Block({ 0.5f, 0.5f, - 0.5f},side[3]),
		// bottom
		Block({- 0.5f, -0.5f, 0.5f}, bot[0]),
		Block({0.5f, -0.5f, 0.5f}, bot[1]),
		Block({0.5f, -0.5f, - 0.5f}, bot[2]),
		Block({- 0.5f, -0.5f, -0.5f}, bot[3])
	};
  indices = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    8, 9, 10, 10, 11, 8,
    12, 13, 14, 14, 15, 12,
    16, 17, 18, 18, 19, 16,
    20, 21, 22, 22, 23, 20
  };

	std::vector<double> texCoords = {

	};
	return BlockMesh(verticesArray, indices, textures);

}

Type Cube::getType(){
  return type;
}

void Cube::setType(int index){
  if(index == 100){
    isVisible = false;
  } else if(index == 0)
    type = Type::GRASS_TOP;
	else if(index == 1)
		type = Type::GRASS_SIDE;
	else if(index == 2)
		type = Type::GRASS_BOT;
  else isVisible = false;
}

bool Cube::getStatus(){
  return isVisible;
}

void Cube::setStatus(bool isVisible){
   this->isVisible = isVisible;
}

std::vector<Block> Cube::getVerticesArray(){
	return verticesArray;
}

std::vector<int>& Cube::getVisibleSides(){
	return visibleSides;
}
