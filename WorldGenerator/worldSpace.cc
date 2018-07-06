#include "worldSpace.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

WorldSpace::WorldSpace(int width, int length, int height){

    int seed = std::rand() * 100;
    ng = new NoiseGenerator(seed);
   //std::vector<int> vec = pn.getCoordinates(width, length,  rand() * 200 , 4, 2);
   std::vector<int> vec;
   for(int i = 0; i < width; i++){
     for(int j = 0; j < length; j++){
       vec.emplace_back(ng->getHeight(i,j) - 40);
    //   std::cout << "i j " << i << j << "H" << ng->getHeight(i,j) << std::endl;
     }
   }


    std::cout << vec.size() << std::endl;
    mesh = c.createBlockMesh();
    chunkManager = new ChunkManager(width / 16, length / 16, vec);
    blockRenderer.setBlockMesh(mesh);
  }

void WorldSpace::draw(Shader shader){
  blockRenderer.setShader(shader);
  chunkManager->draw(blockRenderer);
}
