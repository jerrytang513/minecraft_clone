#include "program.h"

Program::~Program() {
	if (programID != 0)
		glDeleteProgram(programID);
	for (auto it = shaders.rbegin(); it != shaders.rend(); it++) {
		delete *it;
	}
}

Program::Program() :programID{ glCreateProgram() } {}

void Program::addShader(std::string filepath, GLenum shaderType) {

	Shader* shader = new Shader(filepath, shaderType);
	shader->addShader(programID);
	shaders.emplace_back(shader);
}

void Program::compileProgram() {
	if (!programID)
	{
		printf("Error creating shader program!\n");
		return;
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
	std::cout <<  " Program has been built" << std::endl;

}

GLuint Program::getProgramID() {
	return programID;
}

void Program::use() {
	glUseProgram(programID);
}

void Program::setBool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Program::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Program::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}
