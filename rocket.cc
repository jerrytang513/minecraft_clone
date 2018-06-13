#include "application.h"

using namespace std;
using namespace chrono;

class Rocket :public Application {

	int screenWidth = 1000;
	int screenHeight = 700;
	vector<Object*> obj;
	char* title = (char*)"Rocket";


public:
	Rocket() :Application{ title } {
		init();
	}
private:

	void init() {
		addWindow(1000, 700, title);
		GLFWwindow * win = getCurWindow(title)->getWindow();
		glViewport(0, 0, 1000, 700);
		glfwGetFramebufferSize(win, &screenWidth, &screenHeight);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, screenWidth, 0, screenHeight, 0, 1000);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		Object* ob = new Object(400, 400, -500);
		ob->setMass(1);
		ob->attachCube(40.0, 40.0, 40.0, 50.0);

		Object* ob2 = new Object(800, 400, -500);
		ob2->setMass(1);
		ob2->attachCube(40.0, 40.0, 40.0, 50.0);
		ob2->addForce(AppliedForce(Vec3D(-5, 0, 0)));

		obj.emplace_back(ob);
		obj.emplace_back(ob2);

		Collision *c1 = ob->getCollision();
		CubeCollision *c2 = (CubeCollision*)ob2->getCollision();
	}

	void tick(float time) {
		for (vector<Object*>::iterator it = obj.begin(); it != obj.end(); it++) {
			(*it)->update(time);
		}
	}

	void render() {
		for (vector<Object*>::iterator it = obj.begin(); it != obj.end(); it++) {
			glClear(GL_COLOR_BUFFER_BIT);
			glPushMatrix();
			glTranslatef((*it)->getPosition().x, (*it)->getPosition().y, (*it)->getPosition().z);
			(*it)->rotate(45, Vec3D(1, 1, 1));
			(*it)->draw();
			glPopMatrix();
			glfwSwapBuffers(getCurWindow(title)->getWindow());
			glfwPollEvents();

		}

	}




};
