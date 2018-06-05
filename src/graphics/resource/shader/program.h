#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <vector>
#include <string>
#include "shader.h"


struct ShaderStruct{
  ShaderStruct(std::string filepath, GLenum type):filepath{filepath},type{type}{}
  std::string filepath;
  GLenum type;
};

class Program{

  std::vector<ShaderStruct> shaders;
  GLuint programID;
  std::vector<Shader*> allShaders;

public:
  ~Program();
  Program(std::vector<ShaderStruct> shaders);
  void compileProgram();
  GLuint getProgramID();
  void use();
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;

};

#endif
