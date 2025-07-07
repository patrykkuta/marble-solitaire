#include "ScreenManager.h"

Screen* ScreenManager::currentScreen = nullptr;

void ScreenManager::setScreen(Screen* screen) {
	if (ScreenManager::currentScreen != nullptr) delete ScreenManager::currentScreen;

	ScreenManager::currentScreen = screen;
}

void ScreenManager::renderScreen(Window& window) {
	currentScreen->render(window);
}

ScreenManager::~ScreenManager() {
	if (ScreenManager::currentScreen != nullptr) delete ScreenManager::currentScreen;
}

void ScreenManager::newGameScreen() {
	Screen* screen = new GameScreen();
	ScreenManager::setScreen(screen);
}
