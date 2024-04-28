#include <iostream>
#include <functional>
#include "Window.h"
#include "ScreenManager.h"
#include "GameScreen.h"
#include "Screen.h"
#include "ScreenType.h"
#include "MainMenuScreen.h"

using namespace std;

int main() {

	try {
        Window window(800, 600, "Marble Solitaire");
        ScreenManager screenManager;
        Screen* screen;

        //screen = new GameScreen();
        screen = new MainMenuScreen();

        window.setMouseButtonCallback(Screen::mouse_button_callback_static);
        window.setCursorPosCallback(Screen::cursor_position_callback_static);
        window.setFramebufferSizeCallback(Screen::framebuffer_size_callback_static);

        screenManager.setScreen(screen);

        while (!window.shouldClose()) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            screenManager.renderScreen(window);
            window.swapBuffers();
            window.pollEvents();
        }

        delete screen;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}