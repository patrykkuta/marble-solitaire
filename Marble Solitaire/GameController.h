#pragma once

#include "game.h"
#include <vector>
#include <GL/glew.h>
class GameController
{
private:
	GLuint selectedMarble;
	GLuint selectedEmptySpace;
	Game *game;
public:
	GameController();
	~GameController();
	Game* newGame(const std::vector<std::vector<int>>& configuration, DIFFICULTY difficulty);
	bool move();
	void setMarble(GLuint marble);
	void setEmptySpace(GLuint emptySpace);
	std::vector<std::vector<int>>* getBoard();
};

