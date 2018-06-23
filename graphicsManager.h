#ifndef GRAPHICSMANAGER_H_

#include "window.h";
#include "camera.h";

#define GRAPHICSMANAGER_H_

class GraphicsManager{

  Window* window;
  Camera* camera;
  //Resources resource*;

  ~GraphicsManager();
  void init();

public:

  GraphicsManager();
  void createWindow(int height, int width, char* title);
  void attachCamera(Camera* camera);



};

#endif
