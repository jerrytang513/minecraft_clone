#include "application.h"

using namespace std;
using namespace chrono;

class Test:public Application{

  int screenWidth = 1000;
  int screenHeight = 700;

  vector<Object*> obj;
  char* title = (char*)"Test";
  Mesh *mesh;
  Program* program;


public:
  Test():Application{title}{
    init();
  }
private:

  void init(){
    std::cout << "HE1" << std::endl;

    float vertices[] = {
         // positions          // colors           // texture coords
          0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
          0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
         -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
         -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
     };
     unsigned int indices[] = {
         0, 1, 3, // first triangle
         1, 2, 3  // second triangle
     };

    addWindow(1000,700,title);

    GLFWwindow *win = getCurWindow(title) -> getWindow();
    glViewport(0,0,1000,700);
    glfwGetFramebufferSize(win,&screenWidth,&screenHeight);

    mesh = new Mesh();
    std::cout << "HE" << std::endl;


    mesh->addVertexAttribPointer(3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    mesh->addVertexAttribPointer(3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3 * sizeof(float)));
    mesh->addVertexAttribPointer(2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6 * sizeof(float)));
    mesh->addTextureAttrib("src/graphics/asset/pics/container.jpg", GL_TEXTURE0);
    mesh->createMesh(vertices, indices, 4, 6);

    program = new Program();
    std::cout << "HERHE" << std::endl;

    program->setInt("texture", 0);
    program->addShader("/home/ruijie/physics_engine/src/graphics/resource/shader/vertex.glsl",GL_VERTEX_SHADER);
    program->addShader("/home/ruijie/physics_engine/src/graphics/resource/shader/fragment.glsl",GL_FRAGMENT_SHADER);
    program->compileProgram();
    program->use();


  }

  void tick(float time){

  }

  void render(){
    std::cout << "S" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT);
    program->use();
    mesh->renderMesh();
    glfwSwapBuffers(getCurWindow(title)->getWindow());
    glfwPollEvents();


  }


};
