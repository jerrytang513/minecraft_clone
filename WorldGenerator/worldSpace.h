#ifndef WORLDSPACE_H_
#define WORLDSPACE_H_
#include <vector>
#include "../cube.h"
#include <GL/glew.h>
#include "perlinNoise.h"
#include "../src/Mesh/blockMesh.h"
#include "../shader.h"
#include "Renderer/blockRenderer.h"

struct Coordinate{
  int x;
  int y;
  int z;
  Cube cube;
};
// This class manages the blocks inside the world
class WorldSpace{
  Cube c;
  BlockMesh block;
  BlockRenderer blockRenderer;

  PerlinNoise pn;
  std::vector<Coordinate> coordinates;

public:
  WorldSpace(int width, int length, int height);
  std::vector<Coordinate> getCoordinates();
  void draw(Shader shader);



};

#endif
