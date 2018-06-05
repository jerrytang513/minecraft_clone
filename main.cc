#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "src/graphics/window.h"
#include "src/graphics/resource/shader/program.h"
#include "src/object.h"
#include "src/math/vec3d.h"
#include "src/math/mat4.h"
#include "rocket.cc"
#include "src/graphics/mesh.h"
#include "src/graphics/resource/stb_image.h"

using namespace std::chrono;
using namespace std;
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <chrono>
#include <iostream>
#include <vector>


// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
/*
GLfloat vertices[] = {
	-0.5f,0.5f,-0.5f,
	0.5f,0.5f,-0.5f,
	0.5f,0.5f,0.5f,
	-0.5f,0.5f,0.5f,
	-0.5f,-0.5f,0.5f,
	-0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,0.5f
};

*/

float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    Vec3D cubePositions[] = {
        Vec3D( 0.0f,  0.0f,  0.0f),
        Vec3D( 2.0f,  5.0f, -15.0f),
        Vec3D(-1.5f, -2.2f, -2.5f),
        Vec3D(-3.8f, -2.0f, -12.3f),
        Vec3D (2.4f, -0.4f, -3.5f),
        Vec3D(-1.7f,  3.0f, -7.5f),
        Vec3D( 1.3f, -2.0f, -2.5f),
        Vec3D( 1.5f,  2.0f, -2.5f),
        Vec3D( 1.5f,  0.2f, -1.5f),
        Vec3D(-1.3f,  1.0f, -1.5f)
    };


GLuint VBO, VAO, shader, uniformScale, uniformTransform, uniformRotation;
Program *p;
bool direction = true;
float triOffset = 0.0f;
float degree = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.1f;
std::vector<Mesh*> meshArray;
void CreateTriangle()
{

	unsigned int indices[] = {
		0,3,1,
		1,3,2,
		5,4,6,
		6,4,7,
		2,3,4,
		2,4,7,
		1,0,5,
		1,5,6,
		3,0,5,
		3,5,4,
		1,2,7,
		1,7,6
	};

	Mesh* m = new Mesh();
	m->createMesh(vertices,indices,24,36);
	meshArray.emplace_back(m);
}

void CompileShaders()
{
	std::vector<ShaderStruct> v;
	v.emplace_back(ShaderStruct(string("src/graphics/resource/shader/vertex.glsl"),(GLenum)GL_VERTEX_SHADER));
	v.emplace_back(ShaderStruct(string("src/graphics/resource/shader/fragment.glsl"),(GLenum)GL_FRAGMENT_SHADER));
	p = new Program(v);
	p->compileProgram();
	uniformScale = glGetUniformLocation((unsigned)p->getProgramID(), "scale");
	uniformTransform = glGetUniformLocation((unsigned)p->getProgramID(), "transform");
	uniformRotation = glGetUniformLocation((unsigned)p->getProgramID(), "rotation");

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
	glEnable(GL_DEPTH_TEST);

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

	// OPENGL CODE
	unsigned int VBO, VAO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,2,GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	unsigned int texture1, texture2;

	glGenTextures(1, & texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(string("src/graphics/asset/pics/container.jpg").c_str(), &width, &height, &nrChannels,0);
	if(data){
		std::cout << data << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "FAILED to load texture" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load(string("src/graphics/asset/pics/awesome_face.png").c_str(), &width, &height, &nrChannels, 0);
	// OPENGL CODE

















//	CreateTriangle();
	CompileShaders();

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{



		// Get + Handle user input events
		glfwPollEvents();

		// Clear window
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram((unsigned)p->getProgramID());

		//glm::mat4 model;
		//model = glm::translate(model, Vec3D(triOffset, triOffset, 0.0f));

		for(auto it = meshArray.begin(); it != meshArray.end(); it++){
			(*it)->renderMesh();
		}

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
