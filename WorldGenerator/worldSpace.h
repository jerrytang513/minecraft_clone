#ifndef WORLDSPACE_H_
#define WORLDSPACE_H_
#include <vector>
#include "../cube.h"
#include <GL/glew.h>
#include "perlinNoise.h"
#include "../src/Mesh/blockMesh.h"
#include "../shader.h"

struct Coordinate{
  int x;
  int y;
  int z;
};
// This class manages the blocks inside the world
class WorldSpace{
  Cube c;
  BlockMesh block;
  PerlinNoise pn;
  std::vector<Coordinate> coordinates;

  void generateHeight(int width, int height, int length);
public:
  WorldSpace(int width, int height, int length);
  std::vector<Coordinate> getCoordinates();
  void draw(Shader shader);

};

#endif
