#include <iostream>
#include "GameScreen.h"
#include "Utils.h"
#include "GameObject.h"

GameScreen::GameScreen() : Screen() {
	gameController.newGame(BOARD_CONFIGURATION::CROSS, DIFFICULTY::EASY);

	setupVertices(marbleObj, marbleVao, marbleVbo);
	setupVertices(boardObj, boardVao, boardVbo);
}

GameScreen::~GameScreen() {
}

void GameScreen::render(Window& window) {
	displayBoard(window.getGLFWwindow(), glfwGetTime());
}

void GameScreen::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	screenWidth = width;
	screenHeight = height;
	glViewport(0, 0, width, height);

	offScreenFramebuffer.adjustSize(width, height);
}

void GameScreen::drawSceneForColorPicking() {

	marbleShaderProgram.use();
	marbleShaderProgram.setUniform1i("isRenderedOnScreen", false);

	for (int y = 0; y < 7; y++) {
		for (int x = 0; x < 7; x++) {
			if (marblesPositions[y][x] != glm::vec3(0, 0, 0)) {

				GameObject marble = GameObject(marbleObj, marbleTexture);
				marble.setPosition(marblesPositions[y][x]);
				marble.setScale(0.13f);

				glm::mat4 mvMat = camera.getViewMatrix() * marble.getModelMatrix();

				marbleShaderProgram.setUniform1i("x", y);
				marbleShaderProgram.setUniform1i("y", x);

				marbleShaderProgram.setUniformMatrix4fv("mv_matrix", mvMat);
				marbleShaderProgram.setUniformMatrix4fv("proj_matrix", pMat);

				glBindBuffer(GL_ARRAY_BUFFER, marbleVbo[0]); // Bind the VBO for vertices
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);

				// adjust OpenGL settings and draw model
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LEQUAL);
				glDrawArrays(GL_TRIANGLES, 0, marbleObj.getNumVertices());
			}
		}
	}
}

void GameScreen::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	// Used for rotation
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			Window::rightMouseButton = true;
			glfwGetCursorPos(window, &Window::lastMouseX, &Window::lastMouseY);
		}
		else if (action == GLFW_RELEASE) {
			Window::rightMouseButton = false;
		}
	}
	// Used for selection
	else if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {

			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);

			// Bind the color picking framebuffer
			offScreenFramebuffer.bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Render the scene with unique colors for each object
			drawSceneForColorPicking();

			int viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);

			// Read the color of the pixel at mouse coordinates
			unsigned char pixel[4];
			glReadPixels((int)xpos, viewport[3] - (int)ypos, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

			if ((int)pixel[0] >= 0 && (int)pixel[0] <= 6) {
				vector<vector<int>> board = *(gameController.getBoard());

				if (board[(int)pixel[0]][(int)pixel[1]] == 1) {
					gameController.setMarble({ (int)pixel[0], (int)pixel[1] });
				}
				else if (board[(int)pixel[0]][(int)pixel[1]] == 0) {
					if (gameController.getMarble().first != -1) {
						gameController.setEmptySpace({ (int)pixel[0], (int)pixel[1] });
						gameController.move();
					}
				}
			}

			// Revert to the default framebuffer for rendering on screen
			offScreenFramebuffer.unbind();
		}
		else if (action == GLFW_RELEASE) {
			Window::leftMouseButton = false;
		}
	}
}

void GameScreen::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	// Rotate
	if (Window::rightMouseButton) {
		double deltaX = xpos - Window::lastMouseX;
		double deltaY = ypos - Window::lastMouseY;

		camera.rotate(camera.rotationX() + (float)deltaY / 5, camera.rotationY() + (float)deltaX / 5, 0);

		Window::lastMouseX = xpos;
		Window::lastMouseY = ypos;
	}
}

void GameScreen::setupVertices(ImportedModel model, GLuint vao[], GLuint vbo[]) {
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

void GameScreen::displayBoard(GLFWwindow* window, double currentTime) {
	vector<vector<int>> board = *(gameController.getBoard());
	pMat = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 1000.0f);

	boardShaderProgram.use();

	// build perspective matrix
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;

	GameObject boardModel = GameObject(boardObj, boardTexture);
	boardModel.setPosition(glm::vec3(0,0,0));

	glm::mat4 mvMat = camera.getViewMatrix() * boardModel.getModelMatrix();

	boardShaderProgram.setUniformMatrix4fv("mv_matrix", mvMat);
	boardShaderProgram.setUniformMatrix4fv("proj_matrix", pMat);

	glBindBuffer(GL_ARRAY_BUFFER, boardVbo[0]); // Bind the VBO for vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, boardVbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, boardModel.getTextureID());

	// adjust OpenGL settings and draw model
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, boardObj.getNumVertices());

	// ------------------ MARBLES ------------------

	marbleShaderProgram.use();

	marbleShaderProgram.setUniform1i("isRenderedOnScreen", true);

	for (int y = 0; y < 7; y++) {
		for (int x = 0; x < 7; x++) {
			if (board[y][x] == 1) {

				GameObject marble = GameObject(marbleObj, marbleTexture);
				marble.setPosition(marblesPositions[y][x]);
				marble.setScale(0.13f);

				mvMat = camera.getViewMatrix() * marble.getModelMatrix();

				// copy perspective and MV matrices to corresponding uniform variables
				marbleShaderProgram.setUniformMatrix4fv("mv_matrix", mvMat);
				marbleShaderProgram.setUniformMatrix4fv("proj_matrix", pMat);

				glBindBuffer(GL_ARRAY_BUFFER, marbleVbo[0]); // Bind the VBO for vertices
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, marbleVbo[1]);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(1);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, marble.getTextureID());

				// adjust OpenGL settings and draw model
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LEQUAL);
				glDrawArrays(GL_TRIANGLES, 0, marbleObj.getNumVertices());
			}
		}
	}
}