#include <iostream>
#include "Window.h"
#include "ScreenManager.h"
#include "Screen.h"
#include "EndGameScreen.h"
#include "GameController.h"
#include "StartScreen.h"
#include "SoundManager.h"

using namespace std;

int main() {

	try {
        Window window(1920, 1080, "Marble Solitaire");

        Screen* screen = new StartScreen();

        ScreenManager::setScreen(screen);

        while (!window.shouldClose()) {
            glClearColor(0.95f, 0.93f, 0.89f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (GameController::hasFinished) {
                GameController::hasFinished = false;

                screen = new EndGameScreen(GameController::hasWon);
                ScreenManager::setScreen(screen);
            }

            ScreenManager::renderScreen(window);

            window.swapBuffers();
            window.pollEvents();
        }

        SoundManager::getInstance()->drop();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}