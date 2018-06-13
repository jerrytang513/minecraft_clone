#include "shader.h"

Shader::~Shader() {
	if (shaderID != 0)
		glDeleteShader(shaderID);
	shaderID = 0;
}

Shader::Shader(std::string filepath, GLenum shaderType) :filepath{ filepath }, shaderType{ shaderType }, shaderID{ 0 } {}

std::string Shader::parseShader() {
	std::string code;
	std::ifstream file;
	try {
		file.open(filepath);
		std::stringstream ss;
		ss << file.rdbuf();
		file.close();
		code = ss.str();

	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	return code;
}

void Shader::addShader(GLuint program) {

	shaderID = glCreateShader(shaderType);
	std::string temp = parseShader();
	const char* code = temp.c_str();
	glShaderSource(shaderID, 1, &code, NULL);
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
