#ifndef CUBE_H_
#define CUBE_H_

#include "shape3d.h"
#include <iostream>

class Cube : public Shape3D {

	bool isVisible;
	Type type;
	std::vector<int> visibleSides;


public:

	Cube();
	BlockMesh createBlockMesh();
	/*
		Face Mesh Side data are  (int)
		1. top
		2. bottom
		3. left
		4. right
		5. front
		6. back
	*/
	void addSide(int side);
	BlockMesh createSideMesh();
	Type getType();
	void setType(int index);
	bool getStatus();
	void setStatus(bool isVisible);
	std::vector<Block> getVerticesArray();
	std::vector<int>& getVisibleSides();
};


#endif
