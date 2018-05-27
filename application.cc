#include "application.h"

using namespace std;
using namespace chrono;

Application::Application(char* title):title{title}{
	

}

Application::~Application(){

}

void Application::addWindow(int screenWidth,int screenHeight,char* title){
	std::cout << glGetString(GL_VERSION) << std::endl;
	Window* win = new Window(screenWidth,screenHeight,title);
	win->setViewPort(0,0,screenWidth,screenHeight);
	windows.insert(std::pair<char*,Window*>(title,win));
	setCurWindow(title);
}

void Application::setCurWindow(char* title){
	curWin = windows.find(title)->second;
	curWin->getWindow();
}

Window* Application::getCurWindow(char* title){
	return curWin;
}

void Application::run(){

	auto last_time = chrono::high_resolution_clock::now();
	auto current_time = chrono::high_resolution_clock::now();
	auto last_tick_time = chrono::high_resolution_clock::now();
	double ns = 1000000000.0 / 60.0;
	double delta = 0;
	int frames = 0;
	int updates = 0;
	while(!glfwWindowShouldClose(curWin->getWindow())){
		std::cout << "ASDASD" << std::endl;
		auto now = chrono::high_resolution_clock::now();
		delta += (double)(duration_cast<chrono::nanoseconds>(now - last_time).count() / ns);
		while(delta >= 1){
			tick(duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - last_tick_time).count()/1000000000.0);
			last_tick_time = chrono::high_resolution_clock::now();
			updates ++;
			delta --;
		}
		frames ++;
		render();
		if(duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - current_time).count() > 1000){
			current_time = current_time + std::chrono::milliseconds(1000);
			cout << updates << " ups " << frames << " FPS " << endl;
			updates = 0;
			frames = 0;
		}
	}

}

