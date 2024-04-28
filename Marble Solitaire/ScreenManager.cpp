#include "ScreenManager.h"

Screen* ScreenManager::currentScreen = nullptr;

void ScreenManager::setScreen(Screen* screen) {
	if (ScreenManager::currentScreen != nullptr) delete ScreenManager::currentScreen;

	ScreenManager::currentScreen = screen;
}

void ScreenManager::renderScreen(Window& window) {
	this->currentScreen->render(window);
}

Screen* ScreenManager::getScreen() {
	return currentScreen;
}
