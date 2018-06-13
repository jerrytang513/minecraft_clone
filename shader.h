#ifndef SHADER_H_
#define SHADER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <GL/glew.h>

class Shader {

	std::string filepath;
	GLenum shaderType;
	GLuint shaderID;

public:
	~Shader();
	Shader(std::string filepath, GLenum shaderType);
	std::string parseShader();
	void addShader(GLuint program);
};

#endif
