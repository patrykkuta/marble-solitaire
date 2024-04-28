#pragma once

#include "game.h"
#include <vector>
#include <GL/glew.h>

class GameController
{
private:
	std::pair<short, short> selectedMarble = {-1, -1};
	std::pair<short, short> selectedEmptySpace = { -1, -1 };
	Game *game;
public:
	GameController();
	~GameController();
	Game* newGame(const std::vector<std::vector<int>>& configuration, DIFFICULTY difficulty);
	bool move();
	void setMarble(std::pair<short, short> marble);
	void setEmptySpace(std::pair<short, short> emptySpace);
	std::vector<std::vector<int>>* getBoard();
	std::pair<short, short> getMarble();
	std::pair<short, short> getEmptySpace();
};

