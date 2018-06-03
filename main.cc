#include "src/graphics/window.h"
#include <chrono>
#include "src/object.h"
#include "src/math/vec3d.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "rocket.cc"
#include "src/math/mat4.h"

using namespace std::chrono;
using namespace std;
#include <stdio.h>
#include <string.h>
#include <cmath>


// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

GLuint VBO, VAO, shader, uniformModel;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.1f;

// Vertex Shader code
static const char* vShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
layout (location = 0) in vec3 pos;											  \n\
                                                                              \n\
uniform mat4 model;                                                           \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    gl_Position = model * vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);		  \n\
}";

// Fragment Shader
static const char* fShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
out vec4 colour;                                                               \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    colour = vec4(1.0, 0.0, 0.0, 1.0);                                         \n\
}";

void CreateTriangle()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, 1024, NULL, eLog);
		fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

void CompileShaders()
{
	shader = glCreateProgram();

	if (!shader)
	{
		printf("Failed to create shader\n");
		return;
	}

	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shader, "model");
}

int main()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		printf("GLFW initialisation failed!");
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow Forward Compatbility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	// Get Buffer Size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	CreateTriangle();
	CompileShaders();

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		// Get + Handle user input events
		glfwPollEvents();

		if (direction)
		{
			triOffset += triIncrement;
		}
		else {
			triOffset -= triIncrement;
		}

		if (abs(triOffset) >= triMaxOffset)
		{
			direction = !direction;
		}

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		//glm::mat4 model;
		//model = glm::translate(model, glm::vec3(triOffset, triOffset, 0.0f));
		Vec3D v(0.0f,triOffset,0.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_TRUE, Mat4::translation(v).values);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
	}

	return 0;
}






















/*
void exitInput(GLFWwindow* window){
	if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window,true);
}

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

GLfloat rotationX = 45.0f;
GLfloat rotationY = 45.0f;


int main(){
	Vec3D v(1.0f,2.0f,3.0f);
	Mat4 mat = Mat4::translation(v);


	for(int i = 0; i < 16; i++){
		std::cout << mat.values[i];
	}


*/

/*
	Rocket * rocket = new Rocket();
	std::cout << glGetString(GL_VERSION) << std::endl;
	rocket->run();
*/
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
	float ns = 1000000000.0 / 60.0;
	float delta = 0;
	int frames = 0;
	int updates = 0;
	while(!glfwWindowShouldClose(win)){
		auto now = chrono::high_resolution_clock::now();
		delta += (float)(duration_cast<chrono::nanoseconds>(now - last_time).count() / ns);
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
/*
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
*/
