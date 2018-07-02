#ifndef WORLDSPACE_H_
#define WORLDSPACE_H_
#include <vector>
#include "../cube.h"
#include <GL/glew.h>
#include "perlinNoise.h"
#include "../src/Mesh/blockMesh.h"
#include "../shader.h"
#include "Renderer/blockRenderer.h"
#include "coordinate.h"

// This class manages the blocks inside the world
class WorldSpace{
  Cube c;
  BlockMesh mesh;
  BlockRenderer blockRenderer;

  PerlinNoise pn;
  std::vector<Coordinate> coordinates;

public:
  WorldSpace(int width, int length, int height);
  std::vector<Coordinate> getCoordinates();
  void draw(Shader shader);



};

#endif
