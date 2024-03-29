#include "Utils.h"
#include <SOIL2/soil2.h>

using namespace std;


void Utils::printShaderLog(GLuint shader) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		cout << "Shader Info Log: " << log << endl;
		free(log);
	}
}
void Utils::printProgramLog(int prog) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		cout << "Program Info Log: " << log << endl;
		free(log);
	}
}

bool Utils::checkOpenGLError() {
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		cout << "glError: " << glErr << endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

string Utils::readShaderSource(const char* filePath) {
	string content;
	ifstream fileStream(filePath, ios::in);
	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

GLuint Utils::createShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath) {
	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	string vertShaderStr = readShaderSource(vertexShaderPath);
	string fragShaderStr = readShaderSource(fragmentShaderPath);

	const char* vertShaderSrc = vertShaderStr.c_str();
	const char* fragShaderSrc = fragShaderStr.c_str();
	glShaderSource(vertexShader, 1, &vertShaderSrc, NULL);
	glShaderSource(fragmentShader, 1, &fragShaderSrc, NULL);

	glCompileShader(vertexShader);
	checkOpenGLError();
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1) {
		cout << "vertex compilation failed" << endl;
		printShaderLog(vertexShader);
	}
	glCompileShader(fragmentShader);
	checkOpenGLError();
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1) {
		cout << "fragment compilation failed" << endl;
		printShaderLog(fragmentShader);
	}

	GLuint vfProgram = glCreateProgram();

	// catch errors while linking shaders
	glAttachShader(vfProgram, vertexShader);
	glAttachShader(vfProgram, fragmentShader);
	glLinkProgram(vfProgram);
	checkOpenGLError();
	glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
	if (linked != 1) {
		cout << "linking failed" << endl;
		printProgramLog(vfProgram);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return vfProgram;
}

GLuint Utils::loadTexture(const char* texImagePath) {
	GLuint textureID;
	textureID = SOIL_load_OGL_texture(texImagePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (textureID == 0)	cout << "could not	find texture file" << texImagePath << endl;
	return textureID;
}