#pragma once
#include "Screen.h"
#include "GameScreen.h"

class ScreenManager
{
public:
	static Screen* currentScreen;

	~ScreenManager();
	static void setScreen(Screen* screen);
	static void renderScreen(Window& window);
	static void newGameScreen();
};

