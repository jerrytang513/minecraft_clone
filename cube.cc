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
	return BlockMesh(verticesArray, indices, 0);

}

void Cube::addSide(int side){
  /*
		Face Mesh Side data are  (int)
		1. top
		2. bottom
		3. left
		4. right
		5. front
		6. back
	*/
	visibleSides.emplace_back(side);
  switch(side){
    case 1:
        verticesArray.emplace_back(Block({- 0.5f, 0.5f, 0.5f, 0.0f, 0.0f}));
        verticesArray.emplace_back(Block({0.5f, 0.5f, 0.5f, 1.0f, 0.0f}));
        verticesArray.emplace_back(Block({0.5f, 0.5f, - 0.5f, 1.0f, 1.0f}));
        verticesArray.emplace_back(Block({- 0.5f, 0.5f, - 0.5f, 0.0f, 1.0f}));
      std::cout << side << std::endl;
    case 2:
        verticesArray.emplace_back(Block({- 0.5f, -0.5f, 0.5f, 0.0f, 0.0f}));
        verticesArray.emplace_back(Block({0.5f, -0.5f, 0.5f, 1.0f, 0.0f}));
        verticesArray.emplace_back(Block({0.5f, -0.5f, - 0.5f, 1.0f, 1.0f}));
        verticesArray.emplace_back(Block({- 0.5f, -0.5f, -0.5f, 0.0f, 1.0f}));
      std::cout << side << std::endl;
    case 3:
        verticesArray.emplace_back(Block({- 0.5f, - 0.5f, - 0.5f, 1.0f, 0.0f}));
        verticesArray.emplace_back(Block({- 0.5f, - 0.5f, 0.5f, 0.0f, 0.0f}));
        verticesArray.emplace_back(Block({- 0.5f, 0.5f, 0.5f, 0.0f, 1.0f}));
        verticesArray.emplace_back(Block({- 0.5f, 0.5f, - 0.5f, 1.0f, 1.0f}));
      std::cout << side << std::endl;
    case 4:
        verticesArray.emplace_back(Block({ 0.5f, - 0.5f, 0.5f, 0.0f, 0.0f}));
        verticesArray.emplace_back(Block({ 0.5f, - 0.5f, - 0.5f, 1.0f, 0.0f}));
        verticesArray.emplace_back(Block({ 0.5f, 0.5f, - 0.5f, 1.0f, 1.0f}));
        verticesArray.emplace_back(Block({ 0.5f, 0.5f, 0.5f, 0.0f, 1.0f}));
      std::cout << side << std::endl;
    case 5:
      verticesArray.emplace_back(Block({ - 0.5f, - 0.5f, 0.5f, 0.0f, 0.0f}));
      verticesArray.emplace_back(Block({ 0.5f, - 0.5f, 0.5f, 1.0f, 0.0f}));
      verticesArray.emplace_back(Block({ 0.5f, 0.5f, 0.5f, 1.0f, 1.0f}));
      verticesArray.emplace_back(Block({ - 0.5f, 0.5f, 0.5f, 0.0f, 1.0f}));
      std::cout << side << std::endl;
    case 6:
        verticesArray.emplace_back(Block({ 0.5f, - 0.5f, - 0.5f, 1.0f, 0.0f}));
        verticesArray.emplace_back(Block({ - 0.5f, - 0.5f, - 0.5f, 0.0f, 0.0f}));
        verticesArray.emplace_back(Block({ - 0.5f, 0.5f, - 0.5f, 0.0f, 1.0f}));
        verticesArray.emplace_back(Block({ 0.5f, 0.5f, - 0.5f, 1.0f, 1.0f}));
      std::cout << side << std::endl;
  }
}

BlockMesh Cube::createSideMesh(){
  indices = {
    0, 1, 2, 2, 3, 0
  };
  return BlockMesh(verticesArray, indices, type);
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
