#pragma once
#include <GL/glew.h>
class Framebuffer
{
private:
	GLuint id, colorTexture, depthRenderbuffer;

public:
	Framebuffer();
	~Framebuffer();
	void adjustSize(int width, int height);
	void unbind();
	void bind();
};

