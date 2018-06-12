#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include "src/object.h"
#include "src/math/vec3d.h"
#include "src/graphics/window.h"
#include "src/graphics/mesh.h"
#include "src/graphics/resource/shader/program.h"
#include <map>
#include <iterator>
#include <string>

class Application{

	int screenWidth,screenHeight;
	char* title;
	std::map<char*,Window*> windows;
	Window* curWin;

	public:
	Application(char* title);
	~Application();
	virtual void render() = 0;
	virtual void tick(float) = 0;

// Methods for input

	void addWindow(int screenWidth,int screenHeight,char* title);
	void setCurWindow(char* title);
	Window* getCurWindow(char* title);

	virtual void init() = 0;
	void run();

};

#endif
