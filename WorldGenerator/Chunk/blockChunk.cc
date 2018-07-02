#include "blockChunk.h"
BlockChunk():coords{}{}
BlockChunk(std::vector<std::vector<int>> heights){
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      for(int k = 0; k < heights[i][j]; k++){
        Coordinate coord;
        //TODO coordinate need to include all information about a block
        // Type, isVisible
        coord.
        coords(i,j,k) = Coordinate(i,j,k,);
      }
    }
  }
}

std::vector<Coordinate> getCoords(){
  return coords;
}
