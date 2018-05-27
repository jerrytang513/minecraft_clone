#include "src/graphics/window.h"
#include <chrono>
#include "src/object.h"
#include "src/math/vec3d.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "rocket.cc"

using namespace std::chrono;
using namespace std;

void exitInput(GLFWwindow* window){
	if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window,true);
}

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

GLfloat rotationX = 45.0f;
GLfloat rotationY = 45.0f;

int main(){

	Rocket * rocket = new Rocket();
	std::cout << glGetString(GL_VERSION) << std::endl;
	rocket->run();

	/*
	const char* title = "PHYSICS_ENGINE";

	// Create a Window Object
	Window* window = new Window(SCREEN_WIDTH,SCREEN_HEIGHT,"Physics_Engine");
	window->setViewPort(0,0,1000,700);
	GLFWwindow* win = window->getWindow();
	glfwSetKeyCallback(win,keyCallback);
	glfwSetInputMode(win,GLFW_STICKY_KEYS,1);

	int screenWidth, screenHeight;
	screenWidth = SCREEN_WIDTH;
	screenHeight = SCREEN_HEIGHT;

	glfwGetFramebufferSize(win, &screenWidth, &screenHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,SCREEN_WIDTH,0,SCREEN_HEIGHT,0,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	***************************************************** Add an object
	
	Object* ob = new Object(400,400,-500);
	ob->setMass(1);
	ob->attachCube(40.0,40.0,40.0,50.0);

	Object* ob2 = new Object(800,400,-500);
	ob2->setMass(1);
	ob2->attachCube(40.0,40.0,40.0,50.0);
	//ob2->addContinuousForce(AppliedForce(Vec3D(-10,0,0)));
	ob2->addForce(AppliedForce(Vec3D(-5,0,0)));

	Collision *c1 = ob->getCollision();
	CubeCollision *c2 = (CubeCollision*)ob2->getCollision();

	//ob->addContinuousForce(GravityForce(ob->getMass()));


	//********************************************* Add forces to objects
	// FPS counter
	
	auto last_time = chrono::high_resolution_clock::now();
	auto current_time = chrono::high_resolution_clock::now();
	auto last_tick_time = chrono::high_resolution_clock::now();
	double ns = 1000000000.0 / 60.0;
	double delta = 0;
	int frames = 0;
	int updates = 0;
	while(!glfwWindowShouldClose(win)){
		auto now = chrono::high_resolution_clock::now();
		delta += (double)(duration_cast<chrono::nanoseconds>(now - last_time).count() / ns);
		while(delta >= 1){
			// UPDATE THE OBJECT IMPORTANT !!!
			update(ob,duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - last_tick_time).count()/1000000000.0);
			update(ob2,duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - last_tick_time).count()/1000000000.0);
			
			last_tick_time = chrono::high_resolution_clock::now();
			updates ++;
			delta --;
		}

		// COLLISION DETECTION STAGE
		// 
		std::cout << c1->isCollideWithCube(*c2) << std::endl;
		if(c1->isCollideWithCube(*c2) == 1){

			std::cout << "COLLIDED" << std::endl;
			
		} else {

		render(win,ob->getPosition(),ob);
		render(win,ob2->getPosition(),ob2);
		

		
		}
		//
		// COLLISION DETECTION STAGE
		
		frames ++;
		if(duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - current_time).count() > 1000){
			current_time = current_time + std::chrono::milliseconds(1000);
			cout << updates << " ups " << frames << " FPS " << endl;
			updates = 0;
			frames = 0;
		}
	}
*/

	return 0;
}
void update(Object *ob,float time){
	ob->update(time);
}

void render(GLFWwindow *win,Vec3D pos,Object* ob){
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	//glRotatef(rotationX,1,0,0);
	//glRotatef(rotationY,0,1,0);
	ob->rotate(45,Vec3D(1,1,1));
	ob->draw();
	glPopMatrix();
	glfwSwapBuffers(win);
	glfwPollEvents();
}



