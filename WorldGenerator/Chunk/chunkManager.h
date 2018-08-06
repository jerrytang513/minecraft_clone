#ifndef CHUNKMANAGER_H_
#define CHUNKMANAGER_H_

#include <vector>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

#include "blockChunk.h"
#include "heightChunk.h"
#include "../Renderer/chunkRenderer.h"
#include "../../src/Mesh/mesh.h"
#include "../../src/utility/threadPool.h"
#include "../../vec3d.h"

enum class SIGNAL{
    LEFT,
    RIGHT,
    FRONT,
    BACK
};

class ChunkManager{
  // Need 3 dimensional chunks
  std::vector<std::vector<std::vector<BlockChunk>>> m_chunks;
  std::vector<std::vector<std::shared_ptr<HeightChunk>>> m_heightChunks;

  std::vector<std::shared_ptr<ChunkMesh>> renderList;
  int M_WIDTH;
  int M_HEIGHT;
  int M_LENGTH;

  int centerX;
  int centerY;

  bool isHeightReady;
  bool isChunkReady;
  bool isProcessing;
  bool isProcessing2;
  bool isNeedUpdate;
  std::queue<SIGNAL> signal_queue;
  void checkSignal();

  std::mutex boardLock;
  std::mutex processLock;
  std::mutex initHeightLock;
  std::mutex initMeshLock;


public:
  ChunkManager(int width, int length);
  void draw(ChunkRenderer renderer);
  void initMesh(int startWidth, int startLength, int width, int length);
  void initHeight();
  void updateChunks(int startWidth, int startLength, int width, int length);
  void addChunks();
  bool hasProcess();

  // Used to load and unload height chunks
  void moveFront();
  void moveBack();
  void moveLeft();
  void moveRight();

  void moveFront(int num);
  void moveBack(int num);
  void moveLeft(int num);
  void moveRight(int num);

  void processBack();
  void processFront();
  void processLeft();
  void processRight();

  void waitForHeight(int firstWidth, int firstLength, int secondWidth, int secondLength, SIGNAL signal);
};
#endif
