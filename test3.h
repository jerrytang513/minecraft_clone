#ifndef TEST3_H_
#define TEST3_H_

#include "application.h"
#include <iostream>

#include "stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;
using namespace chrono;


class Test3 :public Application {
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	vector<Object*> obj;
	char* title = (char*)"Test3";
	Program* program;

public:
	Test3();
private:
	void init();
	void tick(float time);
	void render();




};
#endif
