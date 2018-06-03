#include "shader.h"

Shader::~Shader(){
  if(shaderID != 0)
    glDeleteShader(shaderID);
  shaderID = 0;
}

Shader::Shader(std::string filepath, GLenum shaderType):filepath{filepath},shaderType{shaderType},shaderID{0}{}

std::string Shader::parseShader(){
  std::ifstream fstream(filepath);
  std::string line;
  std::stringstream ss;
  std::cout << filepath << std::endl;

  while(getline(fstream,line)){
      ss << line << '\n';
  }
  return ss.str();
}

void Shader::addShader(GLuint program){

    shaderID = glCreateShader(shaderType);
    std::string code[1];
    code[0] = parseShader();
    GLint length[1];
    length[0] = code[0].length();
    glShaderSource(shaderID, 1, (char* const*)code, length);
    glCompileShader(shaderID);
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if (!result)
    {
    	glGetShaderInfoLog(shaderID, sizeof(eLog), NULL, eLog);
    	printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
    	return;
    }
    std::cout << shaderType << " : has been attached" << std::endl;
    glAttachShader(program, shaderID);
}
