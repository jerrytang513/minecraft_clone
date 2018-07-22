#ifndef WORLDGENERATOR_CHUNK_HEIGHTCHUNK_H_
#define WORLDGENERATOR_CHUNK_HEIGHTCHUNK_H_

#include <vector>
#include <memory>
#include "../Renderer/direction.h"
#include "blockChunk.h"
#include "../NoiseGen/noiseGen.h"

class HeightChunk{

  unsigned int m_id;
  int m_width;
  int m_length;

  int m_initWidth;
  int m_initLength;
  int max_height = INT_MIN;

  std::vector<int> height;
  std::vector<BlockChunk> m_chunks;

  // Build the chunk
  void init();

  // This will add all the faces in the block chunk
  void addHeightFace();

public:

  HeightChunk(int m_id, int m_width, int m_height, int m_initWidth, int m_initHeight);

  // The World Space will render all of its height chunks, and height chunks will render all of its block chunks
  void render();

  // This will use the noise generator to generate its height and build block chunks
  void generateHeight();

  // Specify the block that need to be updated, and pass in 4 surrounding height chunks
  // If the shared_ptr to the surrounding height chunk is nullptr, then it means the side is facing edge.
  void updateBlockChunk(int height, std::shared_ptr<HeightChunk> left, std::shared_ptr<HeightChunk> right, std::shared_ptr<HeightChunk> front, std::shared_ptr<HeightChunk> back);

  unsigned int get_id();

  // Get the height of the height Chunk
  int getHeight();

  // Check if the height chunk has the height
  bool hasHeight(int height);

  // Get the block chunks
  BlockChunk& getBlockChunk(int height);

  // Insert another block chunk and generate chunk mesh for the block chunk at height for current height chunk's block chunk
  void testBlockChunksLeftRight(int height, BlockChunk& bc, Direction dir);
  // Insert top and down chunk mesh for the block chunk at the height
  void testBlockChunksTopDown(int height);


};

#endif
