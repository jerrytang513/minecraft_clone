#include "threadPool.h"


ThreadPool* ThreadPool::getInstance(){
  if(instance == nullptr){
	  instance = new ThreadPool(4);
    instance->init();
  }
  return instance;
}

ThreadPool* ThreadPool::instance = nullptr;
