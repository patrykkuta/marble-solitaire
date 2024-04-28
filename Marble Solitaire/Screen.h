#pragma once
#include "Window.h"

class Screen
{
protected:
	float screenWidth = 800;
	float screenHeight = 600;
public:
	virtual ~Screen() = 0;
	virtual void render(Window& window) = 0;

	virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) = 0;
	virtual void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) = 0;
	virtual void framebuffer_size_callback(GLFWwindow* window, int width, int height) = 0;

	static void mouse_button_callback_static(GLFWwindow* window, int button, int action, int mods);
	static void cursor_position_callback_static(GLFWwindow* window, double xpos, double ypos);
	static void framebuffer_size_callback_static(GLFWwindow* window, int width, int height);
};

