#include "worldSpace.h"
#include <cstdlib>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

WorldSpace::WorldSpace(int width, int length, int height){

  std::vector<int> vec = pn.getCoordinates(width, length,  rand() , 4, 2);
  std::cout << vec.size() << std::endl;
  mesh = c.createBlockMesh();
  chunkManager = new ChunkManager(width / 16, length / 16, vec);
  blockRenderer.setBlockMesh(mesh);

}


void WorldSpace::draw(Shader shader){

  blockRenderer.setShader(shader);
  chunkManager->draw(blockRenderer);

}
