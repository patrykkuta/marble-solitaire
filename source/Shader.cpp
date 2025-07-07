#include "Shader.h"
#include "Utils.h"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	id = createShaderProgram(vertexShaderPath, fragmentShaderPath);
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::use()
{
	glUseProgram(id);
}

GLint Shader::getUniformLocation(const char* name)
{
	if (uniformLocationsCache.find(name) != uniformLocationsCache.end()) {
		return uniformLocationsCache[name];
	}

	GLint location = glGetUniformLocation(id, name);
	uniformLocationsCache[name] = location;
	return location;
}

void Shader::setUniform1i(const char* name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform3fv(const char* name, const glm::vec3& vec) {
	glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(vec));
}

void Shader::setUniformMatrix4fv(const char* name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

string Shader::readShaderSource(const char* shaderPath) {
	string content;
	ifstream fileStream(shaderPath, ios::in);
	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

GLuint Shader::createShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath) {
	GLuint shaderProgram = glCreateProgram();

	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderPath);
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

	// catch errors while linking shaders
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	Utils::checkOpenGLError();

	GLint linked;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
	if (linked != 1) {
		cout << "linking failed" << endl;
		Utils::printProgramLog(shaderProgram);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

GLuint Shader::createShader(GLuint type, const char* shaderPath)
{
	GLuint shader = glCreateShader(type);
	string shaderSource = readShaderSource(shaderPath);
	const char* shaderSourcePointer = shaderSource.c_str();
	glShaderSource(shader, 1, &shaderSourcePointer, NULL);

	compileShader(shader);

	return shader;
}

void Shader::compileShader(GLuint shader)
{
	GLint shaderCompiled; 

	glCompileShader(shader);
	Utils::checkOpenGLError();
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != 1) {
		cout << "vertex compilation failed" << endl;
		Utils::printShaderLog(shader);
	}
}
