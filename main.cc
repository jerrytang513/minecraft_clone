#include "src/graphics/window.h"
#include "src/object.h"
#include "src/math/vec3d.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

void exitInput(GLFWwindow* window){
	if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window,true);
}

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

void keyCallback( GLFWwindow *window, int key, int scancode, int action, int mods);
void drawCube( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);

GLfloat rotationX = 45.0f;
GLfloat rotationY = 45.0f;

int main(){

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
	
	while(!glfwWindowShouldClose(win)){

		glClear(GL_COLOR_BUFFER_BIT);

		// Render OPENGL
		glPushMatrix();
		glTranslatef( 60, 400, -500);
		// The angle and the axis vector
		glRotatef( rotationX,1,0,0 );
		glRotatef( rotationY,0,1,0 );
		drawCube(40.0f,40.0f,100.0f,50.0f);
		
		glPopMatrix();


		glfwSwapBuffers(win);
		// poll events will check if any keyboard etc events has been triggered.
		glfwPollEvents();
	}
	
	return 0;
}


void drawCube( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength){
	GLfloat halfSideLength = edgeLength * 0.5f;
	   GLfloat vertices[] =
    {
        // front face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left
        
        // back face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom left
        
        // left face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left
        
        // right face
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left
        
        // top face
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // bottom left
        
        // top face
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // top left
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // top right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // bottom left
    };
    
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer( 3, GL_FLOAT, 0, vertices);

	glDrawArrays( GL_QUADS, 0, 24);
	glDisableClientState( GL_VERTEX_ARRAY);

}
