#ifndef TEST_H_
#define TEST_H_

#include "application.h"
#include <iostream>

using namespace std;
using namespace chrono;


class Test :public Application {

	int screenWidth = 2000;
	int screenHeight = 700;

	vector<Object*> obj;
	char* title = (char*)"Test";
	Program* program;

	public:
	Test();
	private:
	void init();
	void tick(float time);
	void render();






};



#endif
