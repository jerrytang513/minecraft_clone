#include "cube.h"

Cube::Cube():Shape3D(){

}

BlockMesh Cube::createBlockMesh(){
	verticesArray = {
		// top
		Block({- 0.5f, 0.5f, 0.5f, 0.0f, 0.0f}),
		Block({0.5f, 0.5f, 0.5f, 1.0f, 0.0f}),
		Block({0.5f, 0.5f, - 0.5f, 1.0f, 1.0f}),
		Block({- 0.5f, 0.5f, - 0.5f, 0.0f, 1.0f}),
		// left
		Block({- 0.5f, - 0.5f, - 0.5f, 1.0f, 0.0f}),
		Block({- 0.5f, - 0.5f, 0.5f, 0.0f, 0.0f}),
		Block({- 0.5f, 0.5f, 0.5f, 0.0f, 1.0f}),
		Block({- 0.5f, 0.5f, - 0.5f, 1.0f, 1.0f}),
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
		Block({ 0.5f, - 0.5f, - 0.5f, 1.0f, 0.0f}),
		Block({ - 0.5f, - 0.5f, - 0.5f, 0.0f, 0.0f}),
		Block({ - 0.5f, 0.5f, - 0.5f, 0.0f, 1.0f}),
		Block({ 0.5f, 0.5f, - 0.5f, 1.0f, 1.0f}),
		// bottom
		Block({- 0.5f, -0.5f, 0.5f, 0.0f, 0.0f}),
		Block({0.5f, -0.5f, 0.5f, 1.0f, 0.0f}),
		Block({0.5f, -0.5f, - 0.5f, 1.0f, 1.0f}),
		Block({- 0.5f, -0.5f, -0.5f, 0.0f, 1.0f})
	};
  indices = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    8, 9, 10, 10, 11, 8,
    12, 13, 14, 14, 15, 12,
    16, 17, 18, 18, 19, 16,
    20, 21, 22, 22, 23, 20
  };
	std::vector<Texture> textures = {
	    Texture("resources/blocks/grass_top.png"),
	    Texture("resources/blocks/grass_side.png"),
	    Texture("resources/blocks/grass_bot.png")
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
