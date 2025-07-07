#pragma once
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>

class Utils {
public:
	static void printShaderLog(GLuint shader);

	static void printProgramLog(int prog);

	static bool checkOpenGLError();

	static std::string readShaderSource(const char* filePath);

	static GLuint createShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);

	static GLuint loadTexture(const char* texImagePath);

};
