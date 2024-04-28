#pragma once
#include "Screen.h"
#include "GameScreen.h"

class ScreenManager
{
public:
	static Screen* currentScreen;

	void setScreen(Screen* screen);
	void renderScreen(Window& window);
	Screen* getScreen();
};

