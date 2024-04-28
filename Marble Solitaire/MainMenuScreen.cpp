#include "MainMenuScreen.h"
#include <iostream>
#include <vector>

MainMenuScreen::MainMenuScreen()
{
	projectionMatrix = glm::perspective(glm::radians(60.0f), screenWidth / screenHeight, 0.1f, 1000.0f);

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, button.size() * sizeof(float), &button[0], GL_STATIC_DRAW);
}

void MainMenuScreen::render(Window& window)
{
	buttonShader.use();

	buttonShader.setUniformMatrix4fv("proj_matrix", projectionMatrix);

	glm::mat4 mvMat = camera.getViewMatrix();
	buttonShader.setUniformMatrix4fv("mv_matrix", mvMat);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // Bind the VBO for vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, button.size() / 3);
}

void MainMenuScreen::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
}

void MainMenuScreen::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
}

void MainMenuScreen::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	screenWidth = (float)width;
	screenHeight = (float)height;
	glViewport(0, 0, width, height);

	projectionMatrix = glm::perspective(glm::radians(60.0f), screenWidth / screenHeight, 0.1f, 1000.0f);
}
