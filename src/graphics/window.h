#ifndef WINDOW_H_
#define WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window{

	int width;
	int height;
	GLFWwindow *window;
	const char* title_name;
	static bool keys[1024];

	public:

	Window(int width, int height, const char* title);
	~Window();
	int getWidth();
	int getHeight();
	void update();
	void clear() const;
	bool closed() const;
	void setViewPort(int x,int y,int width, int height);
	GLFWwindow* getWindow();

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

};
#endif
