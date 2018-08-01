#include "threadPool.h"


ThreadPool* ThreadPool::getInstance(int instance_num){
  if(instance_num == 0){
    if(ThreadPool::renderThread == nullptr){
      ThreadPool::renderThread = new ThreadPool(6, 0);
	  ThreadPool::renderThread->init();
    }
    return ThreadPool::renderThread;

  } else {
    if(ThreadPool::processThread == nullptr){
      std::cout << "CALLED" << std::endl;

	  ThreadPool::processThread = new ThreadPool(1, 1);
	  ThreadPool::processThread->init();
    }
    return ThreadPool::processThread;
  }
}

ThreadPool* ThreadPool::renderThread = nullptr;
ThreadPool* ThreadPool::processThread = nullptr;
