#ifndef SHADER_H_
#define SHADER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <GL/glew.h>


class Shader{

  std::string filepath;
  GLenum shaderType;
  GLuint shaderID;
  ~Shader();

public:
  Shader(std::string filepath, GLenum shaderType);
  std::string parseShader(const std::string& filepath, GLenum shaderType);
  void addShader(GLuint program, GLenum type, const char* source);



};


#endif
