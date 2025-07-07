#pragma once
#include "Screen.h"
#include "ImportedModel.h"
#include "Camera.h"
#include <vector>
#include "GameController.h"
#include "Framebuffer.h"
#include "Texture.h"
#include "Shader.h"

using namespace std;

class GameScreen : public Screen {
public:
	GameScreen();
	~GameScreen();
	void render(Window& window) override;

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	static ImportedModel marbleObj;
	static ImportedModel boardObj;
	Shader marbleShaderProgram = Shader("shaders/marbleVertex.glsl", "shaders/marbleFragment.glsl");
	Shader boardShaderProgram = Shader("shaders/boardVertex.glsl", "shaders/boardFragment.glsl");
	Texture marbleTexture = Texture("textures/marbleTexture.tga");
	Texture boardTexture = Texture("textures/boardTexture.tga");
	Framebuffer offScreenFramebuffer;
	Camera camera = Camera(glm::vec3(0, 0, 3), glm::vec3(60, 0, 0));
	GameController gameController = GameController();

	GLuint marbleVao[1], boardVao[1];
	GLuint marbleVbo[3], boardVbo[3]; 
	float aspect; 
	glm::mat4 pMat;
	glm::vec3 lightDirection;

	glm::vec3 marblesPositions[7][7] = {
		{glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(-0.275841, 0.17, -0.829844), glm::vec3(0.00116, 0.17, -0.829844), glm::vec3(0.278161, 0.17, -0.829844), glm::vec3(0,0,0), glm::vec3(0,0,0)},
		{glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(-0.275841, 0.17, -0.552842), glm::vec3(0.00116, 0.17, -0.552842), glm::vec3(0.278161, 0.17, -0.552842), glm::vec3(0,0,0), glm::vec3(0,0,0)},
		{glm::vec3(-0.829844, 0.17, -0.275841), glm::vec3(-0.552842, 0.17, -0.275841), glm::vec3(-0.275841, 0.17, -0.275841), glm::vec3(0.00116, 0.17, -0.275841), glm::vec3(0.278161, 0.17, -0.275841), glm::vec3(0.555163, 0.17, -0.275841), glm::vec3(0.832164, 0.17, -0.275841)},
		{glm::vec3(-0.829844, 0.17, 0.00116), glm::vec3(-0.552842, 0.17, 0.00116), glm::vec3(-0.275841, 0.17, 0.00116), glm::vec3(0.00116, 0.17, 0.001161), glm::vec3(0.278161, 0.17, 0.00116), glm::vec3(0.555163, 0.17, 0.00116), glm::vec3(0.832164, 0.17, 0.00116)},
		{glm::vec3(-0.829844, 0.17, 0.278162), glm::vec3(-0.552842, 0.17, 0.278162), glm::vec3(-0.275841, 0.17, 0.278162), glm::vec3(0.00116, 0.17, 0.278162), glm::vec3(0.278161, 0.17, 0.278162), glm::vec3(0.555163, 0.17, 0.278162), glm::vec3(0.832164, 0.17, 0.278162)},
		{glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(-0.275841, 0.17, 0.555163), glm::vec3(0.00116, 0.17, 0.555163), glm::vec3(0.278161, 0.17, 0.555163), glm::vec3(0,0,0), glm::vec3(0,0,0)},
		{glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(-0.275841, 0.17, 0.832164), glm::vec3(0.00116, 0.17, 0.832164), glm::vec3(0.278161, 0.17, 0.832164), glm::vec3(0,0,0), glm::vec3(0,0,0)}
	};

	void drawSceneForColorPicking();
	void setupVertices(ImportedModel model, GLuint vao[], GLuint vbo[]);
	void displayBoard(GLFWwindow* window, double currentTime);
};

