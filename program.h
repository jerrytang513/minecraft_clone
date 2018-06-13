#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <vector>
#include <string>
#include "shader.h"



class Program {

	std::vector<Shader*> shaders;
	GLuint programID;

public:
	~Program();
	Program();
	void compileProgram();
	GLuint getProgramID();

	void addShader(std::string filepath, GLenum shaderType);
	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

};

#endif
