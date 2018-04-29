#include "src/graphics/window.h"

int main(){

	const char* title = "PHYSICS_ENGINE";

	Window window(1000,1000,"Physics Engine");
	
	while(!window.closed()){
		window.clear();
		window.update();
	}


	return 0;
}
