#pragma once
#include <stack>
#include <queue>
#include <vector>
#include "board_configuration.h"
#include "difficulty.h"
#include "move.h"

class Game {
private:
	std::vector<std::vector<int>> board;
	unsigned int difficulty;

	bool isMoveValid(int originY, int originX, int destinationY, int destinationX);
public:
	Game(const std::vector<std::vector<int>>& configuration, DIFFICULTY difficulty);
	std::vector<std::vector<int>>* getBoard();
	bool performMove(Move move);
	bool hasWon();
	bool hasFinished();
	void setDifficulty(DIFFICULTY difficulty);
};

