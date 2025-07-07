#include "Texture.h"

Texture::Texture(const char* textureImagePath)
{
	loadTexture(textureImagePath);
}

void Texture::loadTexture(const char* textureImagePath)
{
	textureID = SOIL_load_OGL_texture(textureImagePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	if (textureID == 0) {
		throw runtime_error("Could not find the texture file.");
	}
}

GLuint Texture::getTextureId()
{
	return textureID;
}
