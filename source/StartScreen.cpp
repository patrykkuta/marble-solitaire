#include "StartScreen.h"
#include "ScreenManager.h"
#include "SoundManager.h"

StartScreen::StartScreen()
{
    SoundManager* soundManager = SoundManager::getInstance();

    soundManager->playInLoop("audio/intro.mp3");

    setupVertices();
    shaderProgram.use();
}

void StartScreen::setupVertices()
{
    // Define the vertices of the square
    std::vector<float> pvalues = {
        -0.8f,  0.8f, 0.0f,  // Top left
         0.8f,  0.8f, 0.0f,  // Top right
         0.8f, -0.8f, 0.0f,  // Bottom right
        -0.8f, -0.8f, 0.0f   // Bottom left
    };

    // Define the texture coordinates
    std::vector<float> tvalues = {
        0.0f, 1.0f,  // Top left
        1.0f, 1.0f,  // Top right
        1.0f, 0.0f,  // Bottom right
        0.0f, 0.0f   // Bottom left
    };

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(2, vbo);

    // VBO for vertex locations
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, pvalues.size() * sizeof(float), &pvalues[0], GL_STATIC_DRAW);

    // VBO for texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, tvalues.size() * sizeof(float), &tvalues[0], GL_STATIC_DRAW);
}

void StartScreen::render(Window& window)
{
    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, startScreen.getTextureId());

    // Bind the VAO
    glBindVertexArray(vao[0]);

    // Enable the attribute arrays
    glEnableVertexAttribArray(0); // vertex position
    glEnableVertexAttribArray(1); // texture coordinates

    // Bind VBO for vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Bind VBO for texture coordinates
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    // Draw the square
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // Disable the attribute arrays
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void StartScreen::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {}

void StartScreen::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {}

void StartScreen::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, width, height);
}

void StartScreen::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        SoundManager* soundManager = SoundManager::getInstance();

        soundManager->stopPlaying();
        soundManager->playOnce("audio/play.mp3");
        ScreenManager::newGameScreen();
    }
}
