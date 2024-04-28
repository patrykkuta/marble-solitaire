#pragma once
#include "Screen.h"
#include "Camera.h"
#include "Shader.h"

using namespace std;

class MainMenuScreen : public Screen
{
private:
	Camera camera = Camera(glm::vec3(0, 0, 3));
	Shader buttonShader = Shader("buttonVertex.glsl", "buttonFragment.glsl");
	glm::mat4 projectionMatrix;
	GLuint vao[1], vbo[1];

	vector<float> button = {
		-1.0f, -0.5f, 0.0f,
		1.0f, 0.5f, 0.0f,
		-1.0f, 0.5f, 0.0f,

		-1.0f, -0.5f, 0.0f,
		1.0f, -0.5f, 0.0f,
		1.0f, 0.5f, 0.0f,
	};

public:
	MainMenuScreen();
	void render(Window& window) override;
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) override;
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) override;
	void framebuffer_size_callback(GLFWwindow* window, int width, int height) override;
};

