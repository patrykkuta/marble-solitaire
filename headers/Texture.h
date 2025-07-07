#pragma once
#include <GL/glew.h>
#include <SOIL2/SOIL2.h>
#include <stdexcept>

using namespace std;

class Texture
{
private:
	GLuint textureID = 0;

public:
	Texture(const char* textureImagePath);
	void loadTexture(const char* textureImagePath);
	GLuint getTextureId();
};

