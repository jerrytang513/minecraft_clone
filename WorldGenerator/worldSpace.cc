#include "worldSpace.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

WorldSpace::WorldSpace(int width, int length, int height){
  setHeight(width, length, height);
}

void WorldSpace::setHeight(int width, int length, int height){
  int seed = std::rand() * 10;
  ng = new NoiseGenerator(seed);
 //std::vector<int> vec = pn.getCoordinates(width, length,  rand() * 200 , 4, 2);
 std::vector<int> vec;
 for(int i = 0; i < width; i++){
   for(int j = 0; j < length; j++){
     vec.emplace_back(ng->getHeight(i,j) - 90);
   }
 }
 chunkManager = new ChunkManager(width / 16, length / 16, vec);
  // Generate and set the chunk mesh for every chunks
  std::cout << "INIT MESH " << std::endl;
  chunkManager->initMesh();
}


void WorldSpace::draw(Shader shader){

    chunkRenderer.setShader(shader);
    chunkManager->draw(chunkRenderer);

}
