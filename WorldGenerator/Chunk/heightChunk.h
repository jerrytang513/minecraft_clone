#ifndef WORLDGENERATOR_CHUNK_HEIGHTCHUNK_H_
#define WORLDGENERATOR_CHUNK_HEIGHTCHUNK_H_

#include <vector>
#include <memory>
#include <algorithm>
#include <mutex>
#include <thread>
#include <chrono>

#include "blockChunk.h"

#include "../Renderer/direction.h"
#include "../NoiseGen/noiseGen.h"
#include "../../src/Mesh/chunkMesh.h"


enum class STATUS{
  NONE,
  PROCESSING,
  HEIGHTREADY,
  MESHREADY
};

class HeightChunk{

  int m_width;
  int m_length;

  int m_initWidth;
  int m_initLength;
  int max_height = INT_MIN;

  bool m_isHeightReady;
  bool m_isMeshReady;
  bool m_isNeedUpdate;
  bool m_isProcessing;
  bool m_isTypeReady;

  std::vector<int> m_height;
  std::vector<BlockChunk> m_chunks;
  std::vector<ChunkMesh> m_meshes;

  STATUS curStatus;
  // Build the chunk
  void init();

  // This will add all the faces in the block chunk
  void addHeightFace();

public:

  HeightChunk(int m_width, int m_height, int m_initWidth, int m_initHeight);

  // The World Space will render all of its height chunks, and height chunks will render all of its block chunks

  // This will use the noise generator to generate its height and build block chunks
  void generateHeight();

  // Specify the block that need to be updated, and pass in 4 surrounding height chunks
  // If the shared_ptr to the surrounding height chunk is nullptr, then it means the side is facing edge.
  void updateBlockChunk(int height, std::shared_ptr<HeightChunk> left, std::shared_ptr<HeightChunk> right, std::shared_ptr<HeightChunk> front, std::shared_ptr<HeightChunk> back);
  void updateHeightChunk(std::shared_ptr<HeightChunk> left, std::shared_ptr<HeightChunk> right, std::shared_ptr<HeightChunk> front, std::shared_ptr<HeightChunk> back);


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

  void testBlockChunksFrontBack(int height,  std::shared_ptr<HeightChunk> front,  std::shared_ptr<HeightChunk>  back);
  void testBlockChunksLeftRight(int height, std::shared_ptr<HeightChunk> left,  std::shared_ptr<HeightChunk>  right);

  std::vector<std::shared_ptr<ChunkMesh>> getChunkMesh();


  bool isHeightReady();
  bool isMeshReady();
  bool isNeedUpdate();
  void setIsNeedUpdate(bool m_isNeedUpdate);
  bool isProcessing();
  void setIsProcessing(bool m_isProcessing);

  int getWidth();
  int getLength();
  int getInitWidth();
  int getInitLength();
  STATUS getStatus();
  void clearMesh();

  void addLeftMesh(std::shared_ptr<HeightChunk> left);
  void addRightMesh(std::shared_ptr<HeightChunk> right);
  void addFrontMesh(std::shared_ptr<HeightChunk> front);
  void addBackMesh(std::shared_ptr<HeightChunk> back);

};

#endif
