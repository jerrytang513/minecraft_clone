#include "test.h"

Test::Test() :Application{ title } {
	init();
}

void Test::init() {
/*
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

	addWindow(1000, 700, title);
	GLFWwindow *win = getCurWindow()->getWindow();

	mesh = new Mesh();

	mesh->addVertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	mesh->addVertexAttribPointer(3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	mesh->addVertexAttribPointer(2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	mesh->addTextureAttrib("container.jpg", GL_TEXTURE0);
	mesh->createMesh(vertices, indices, 4, 6);

	program = new Program();

	program->addShader("vertex.glsl", GL_VERTEX_SHADER);
	program->addShader("fragment.glsl", GL_FRAGMENT_SHADER);
	program->compileProgram();
	program->use();
	program->setInt("texture", 0);
*/
}

void Test::tick(float time) {
}

void Test::render() {

}
