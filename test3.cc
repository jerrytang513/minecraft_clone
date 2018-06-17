#include "test3.h"
#include "mat4.h"


Test3::Test3() : Application{ title }{
  init();
}

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void Test3::init(){
	addWindow(SCR_WIDTH, SCR_HEIGHT, title);
  GLFWwindow * window = getCurWindow() -> getWindow();
  Program * program = new Program();
  program->addShader("vertex2.glsl", GL_VERTEX_SHADER);
  program->addShader("fragment2.glsl", GL_FRAGMENT_SHADER);
  program->compileProgram();
  float vertices[] = {
  0.5f,  0.5f, 0.0f,    1.0f, 1.0f, // top right
  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
  -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
  0.5f,  0.5f,  0.0f,  0.0f, 1.0f  // top left
  };
  unsigned int indices[] = {
    3, 0, 1,
    2, 1, 0
  };
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  unsigned int texture;

  glGenTextures(1, & texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(string("container.jpg").c_str(), &width, &height, &nrChannels, 0);
  if(data){
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  stbi_image_free(data);

  program->use();
  program->setInt("texture1", 0);

  while(!glfwWindowShouldClose(window)){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    program->use();
	Vec3D vie = Vec3D(0.0f, 0.0f, -3.0f);
    Mat4 rotate = Mat4::rotation(-55.0f, Vec3D(1.0f,0.0f,0.0f));
    Mat4 view = Mat4::translation(vie);
    Mat4 projection = Mat4::perspective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    unsigned int modelLoc = glGetUniformLocation(program->getProgramID(), "model");
    unsigned int viewLoc = glGetUniformLocation(program->getProgramID(), "view");
    unsigned int projectionLoc = glGetUniformLocation(program->getProgramID(), "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, rotate.values);
    glUniformMatrix4fv(viewLoc,1, GL_FALSE, view.values);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.values);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();

  }

}

void Test3::render(){

}

void Test3::tick(float real){

}
