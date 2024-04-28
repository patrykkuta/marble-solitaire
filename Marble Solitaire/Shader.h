#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <unordered_map>

using namespace std;

class Shader
{
private:
	GLuint id;
	string readShaderSource(const char* shaderPath);
	GLuint createShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	GLuint createShader(GLuint type, const char* shaderPath);
	void compileShader(GLuint shader);
	GLint getUniformLocation(const char* name);
	unordered_map<string, GLint> uniformLocationsCache;

public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	~Shader();
	void use();
	void setUniform1i(const char* name, int value);
	void setUniformMatrix4fv(const char* name, const glm::mat4& matrix);

};

