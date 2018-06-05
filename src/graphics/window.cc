#include "window.h"

bool Window::keys[1024];
//void keyCallback(GLFWwindow*window, int key, int scancode, int action,int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void error_callback(int error, const char* description){
	std::cout << "Error " << description << std::endl;
}

Window::Window(int width, int height, const char* title){
	if(!glfwInit()){
		std::cout << "CANNOT initialize with glfwInit()" << std::endl;
	} else {
		this->window = glfwCreateWindow(width,height,title,NULL,NULL);
	}

	// Set the version number
  	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window,this);
	//glfwSetKeyCallback(window,keyCallback);
	glfwSetErrorCallback(error_callback);
	// When resize happens, reset the values for the viewport.
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
	if(glewInit() != GLEW_OK){
		std::cout << "CANNOT initialize with glfwInit()" << std::endl;
	}
	// Initilize all the keys
	for(int i = 0; i < 1024; i++){
		keys[i] = false;
	}
}

GLFWwindow* Window::getWindow(){
	return window;
}
void Window::setViewPort(int x,int y, int width, int height){
	glViewport(x,y,width,height);
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

void Window::framebuffer_size_callback(GLFWwindow* window,int width, int height){
	glViewport(0,0,width,height);

}
/*
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	Window* win = (Window*) glfwGetWindowUserPointer(window);
	win->keys[key] = action != GLFW_RELEASE;
}
*/
