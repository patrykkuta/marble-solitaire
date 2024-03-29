#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "board_configuration.h"
#include "difficulty.h"
#include "GameController.h"
#include "ImportedModel.h"
#include "Utils.h"

using namespace std;

ImportedModel marbleObj("marble.obj");
ImportedModel boardObj("board.obj");

GLuint marbleVao[1], marbleVbo[3];
GLuint boardVao[1], boardVbo[3];
float cameraX, cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;
GLuint marbleRenderingProgram, boardRenderingProgram;
vector<vector<int>> board;
float spacing = 3.0f;
GLuint marbleTexture;
GLuint boardTexture;
float rotationAngleX = 75;
float rotationAngleY = 0;

glm::vec3 marblesPositions[7][7] = {
	{glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(-0.275841, 0.829844, 0.17), glm::vec3(0.00116, 0.829844, 0.17), glm::vec3(0.278161, 0.829844, 0.17), glm::vec3(0,0,0), glm::vec3(0,0,0)},
	{glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(-0.275841, 0.552842, 0.17), glm::vec3(0.00116, 0.552842, 0.17), glm::vec3(0.278161, 0.552842, 0.17), glm::vec3(0,0,0), glm::vec3(0,0,0)},
	{glm::vec3(-0.829844, 0.275841, 0.17), glm::vec3(-0.552842, 0.275841, 0.17), glm::vec3(-0.275841, 0.275841, 0.17), glm::vec3(0.00116, 0.275841, 0.17), glm::vec3(0.278161, 0.275841, 0.17), glm::vec3(0.555163, 0.275841, 0.17), glm::vec3(0.832164, 0.275841, 0.17)},
	{glm::vec3(-0.829844, -0.00116, 0.17), glm::vec3(-0.552842, -0.00116, 0.17), glm::vec3(-0.275841, -0.00116, 0.17), glm::vec3(0.00116, -0.001161, 0.17), glm::vec3(0.278161, -0.00116, 0.17), glm::vec3(0.555163, -0.00116, 0.17), glm::vec3(0.832164, -0.00116, 0.17)},
	{glm::vec3(-0.829844, -0.278162, 0.17), glm::vec3(-0.552842, -0.278162, 0.17), glm::vec3(-0.275841, -0.278162, 0.17), glm::vec3(0.00116, -0.278162, 0.17),glm::vec3(0.278161, -0.278162, 0.17), glm::vec3(0.555163, -0.278162, 0.17), glm::vec3(0.832164, -0.278162, 0.17)},
	{glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(-0.275841, -0.555163, 0.17), glm::vec3(0.00116, -0.555163, 0.17), glm::vec3(0.278161, -0.555163, 0.17), glm::vec3(0,0,0), glm::vec3(0,0,0)},
	{glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(-0.275841, -0.832164, 0.17), glm::vec3(0.00116, -0.832164, 0.17), glm::vec3(0.278161, -0.832164, 0.17), glm::vec3(0,0,0), glm::vec3(0,0,0)}
};

GameController gameController;

bool rightMouseButton = false;
bool leftMouseButton = false;
double lastMouseX = 0.0;
double lastMouseY = 0.0;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	// Used for rotation
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			rightMouseButton = true;
			glfwGetCursorPos(window, &lastMouseX, &lastMouseY);
		}
		else if (action == GLFW_RELEASE) {
			rightMouseButton = false;
		}
	}
	// Used for selection
	else if (button == GLFW_MOUSE_BUTTON_LEFT) {
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	// Rotate
	if (rightMouseButton) {
		double deltaX = xpos - lastMouseX;
		double deltaY = ypos - lastMouseY;

		rotationAngleX += (float)deltaY/5;
		rotationAngleY += (float)deltaX/5;

		lastMouseX = xpos;
		lastMouseY = ypos;
	}
	// Select
	else if (leftMouseButton) {

	}
}

void setupVertices(ImportedModel model, GLuint vao[], GLuint vbo[]) {
	std::vector<glm::vec3> vert = model.getVertices();
	std::vector<glm::vec2> tex = model.getTextureCoords();
	std::vector<glm::vec3> norm = model.getNormals();
	int numObjVertices = model.getNumVertices();
	std::vector<float> pvalues; // vertex positions
	std::vector<float> tvalues; // texture coordinates
	std::vector<float> nvalues; // normal vectors
	 
	for (int i = 0; i < numObjVertices; i++) {
		pvalues.push_back((vert[i]).x);
		pvalues.push_back((vert[i]).y);
		pvalues.push_back((vert[i]).z);
		tvalues.push_back((tex[i]).s);
		tvalues.push_back((tex[i]).t);
		nvalues.push_back((norm[i]).x);
		nvalues.push_back((norm[i]).y);
		nvalues.push_back((norm[i]).z);
	}
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(3, vbo);
	// VBO for vertex locations
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);
	// VBO for texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, tvalues.size() * 4, &tvalues[0], GL_STATIC_DRAW);
	// VBO for normal vectors
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, &nvalues[0], GL_STATIC_DRAW);
}

void init(GLFWwindow* window) {
	gameController = GameController();
	gameController.newGame(BOARD_CONFIGURATION::TRIANGLE, DIFFICULTY::EASY);
	
	marbleTexture = Utils::loadTexture("marbleTexture.jpg");
	boardTexture = Utils::loadTexture("boardTexture2.jpg");

	marbleRenderingProgram = Utils::createShaderProgram("marbleVertex.glsl", "marbleFragment.glsl");
	boardRenderingProgram = Utils::createShaderProgram("boardVertex.glsl", "boardFragment.glsl");
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 4.0f;
	cubeLocX = 0.0f; cubeLocY = 0.0f; cubeLocZ = 0.0f;

	setupVertices(marbleObj, marbleVao, marbleVbo);
	setupVertices(boardObj, boardVao, boardVbo);
}

void displayBoard(GLFWwindow* window, double currentTime) {
	board = *gameController.getBoard();

	glUseProgram(boardRenderingProgram);

	// get the uniform variables for the MV and projection matrices
	mvLoc = glGetUniformLocation(boardRenderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(boardRenderingProgram, "proj_matrix");

	// build perspective matrix
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;

	pMat = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 1000.0f);

	glm::mat4 rotationMatrixAxisX = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotationMatrixAxisY = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mMat = rotationMatrixAxisX * rotationMatrixAxisY * glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));

	mvMat = vMat * mMat;

	// copy perspective and MV matrices to corresponding uniform variables
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	glBindBuffer(GL_ARRAY_BUFFER, boardVbo[0]); // Bind the VBO for vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, boardVbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, boardTexture);

	// adjust OpenGL settings and draw model
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, boardObj.getNumVertices());

	// ------------------ MARBLES ------------------

	glUseProgram(marbleRenderingProgram);

	// get the uniform variables for the MV and projection matrices
	mvLoc = glGetUniformLocation(marbleRenderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(marbleRenderingProgram, "proj_matrix");

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (board[i][j] == 1) {

				glm::vec3 marblePosition = marblesPositions[i][j];
				glm::mat4 rotateNinety = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

				mMat = rotationMatrixAxisX * rotationMatrixAxisY * rotateNinety * glm::translate(glm::mat4(1.0f), marblePosition);
				mMat = glm::scale(mMat, glm::vec3(0.13f)); // Scale down the marble

				mvMat = vMat * mMat;

				// copy perspective and MV matrices to corresponding uniform variables
				glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
				glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

				glBindBuffer(GL_ARRAY_BUFFER, marbleVbo[0]); // Bind the VBO for vertices
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, marbleVbo[1]);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(1);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, marbleTexture);

				// adjust OpenGL settings and draw model
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LEQUAL);
				glDrawArrays(GL_TRIANGLES, 0, marbleObj.getNumVertices());
			}
		}
	}	
}

int main() {
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Marble Solitaire", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		exit(EXIT_FAILURE);
	}
	glfwSwapInterval(1);

	init(window);

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	// Set cursor position callback
	glfwSetCursorPosCallback(window, cursor_position_callback);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		displayBoard(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}