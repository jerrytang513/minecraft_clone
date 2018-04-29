#include "window.h"

bool Window::keys[1024];
void keyCallback(GLFWwindow*window, int key, int scancode, int action,int mods);

Window::Window(int width, int height, const char* title){
	if(!glfwInit()){
		std::cout << "CANNOT initialize with glfwInit()" << std::endl;	
		glfwTerminate();
	} else {
		this->window = glfwCreateWindow(width,height,title,NULL,NULL);
	}	
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window,this);
	glfwSetKeyCallback(window,keyCallback);
	if(glewInit() != GLEW_OK){
		std::cout << "CANNOT initialize with glfwInit()" << std::endl;
		glfwTerminate();
	}
	// Initilize all the keys
	for(int i = 0; i < 1024; i++){
		keys[i] = false;
	}
}

Window::~Window(){
	glfwTerminate();
}

int Window::getWidth(){
	return this->width;
}

int Window::getHeight(){
	return this->height;
}

void Window::clear() const{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::closed() const{
	return glfwWindowShouldClose(window);
}

void Window::update(){
	glfwSwapBuffers(window);
	glfwPollEvents();
	glfwGetFramebufferSize(window,&width,&height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	Window* win = (Window*) glfwGetWindowUserPointer(window);
	win->keys[key] = action != GLFW_RELEASE;
}
