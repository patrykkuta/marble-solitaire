#pragma once
#include "Screen.h"
#include "Texture.h"
#include "Shader.h"

class StartScreen : public Screen {
private:
	Texture startScreen = Texture("textures/start_screen.tga");
	GLuint vao[1];
	GLuint vbo[2];
	Shader shaderProgram = Shader("shaders/imageVertex.glsl", "shaders/imageFragment.glsl");

public:
	StartScreen();
	void setupVertices();
	void render(Window& window) override;

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) override;
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) override;
	void framebuffer_size_callback(GLFWwindow* window, int width, int height) override;
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
};

