#include "application.h"

Application::Application(char* title):title{title}{
	

}

Application::~Application(){

}

void Application::addWindow(int screenWidth,int screenHeight,char* title){

	Window* win = new Window(screenWidth,screenHeight,title);
	win->setViewPort(0,0,screenWidth,screenHeight);
	windows.insert(std::pair<char*,Window*>(title,win));

}

void Application::setCurWindow(char* title){
	curWin = windows.find(title)->second;
}

Window* Application::getCurWindow(char* title){
	return curWin;
}

