#pragma once

#include "game.h"
class GameController
{
public:
	GameController();
	Game* newGame(const std::vector<std::vector<int>>& configuration, DIFFICULTY difficulty);
};

