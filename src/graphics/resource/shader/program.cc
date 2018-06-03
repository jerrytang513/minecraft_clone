#include "program.h"

Program::~Program(){
    if(programID != 0)
      glDeleteProgram(programID);
    for(auto it = allShaders.rbegin(); it != allShaders.rend(); it++){
      delete *it;
    }
}

Program::Program(std::vector<ShaderStruct> shaders):shaders{shaders},programID{0},allShaders{}{}

void Program::compileProgram(){
  programID = glCreateProgram();
  if (!programID)
  {
    printf("Error creating shader program!\n");
    return;
  }

  // Build all shaders
  for(auto it = shaders.begin(); it != shaders.end(); it++){
    Shader* s = new Shader(it->filepath,it->type);
    s->addShader(programID);
    allShaders.emplace_back(s);
  }

  GLint result = 0;
  GLchar eLog[1024] = { 0 };

  glLinkProgram(programID);
  glGetProgramiv(programID, GL_LINK_STATUS, &result);
  if (!result)
  {
    glGetProgramInfoLog(programID, sizeof(eLog), NULL, eLog);
    printf("Error linking program: '%s'\n", eLog);
    return;
  }

  glValidateProgram(programID);
  glGetProgramiv(programID, GL_VALIDATE_STATUS, &result);
  if (!result)
  {
    glGetProgramInfoLog(programID, sizeof(eLog), NULL, eLog);
    printf("Error validating program: '%s'\n", eLog);
    return;
  }
}

GLuint Program::getProgramID(){
  return programID;
}
