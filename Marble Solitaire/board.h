#pragma once
#include "board_configuration.h"
#include "difficulty.cpp"

class Board {
private:
	int board[7][7];
public:
	Board(BOARD_CONFIGURATION configuration, DIFFICULTY difficulty);
	int(*getBoard())[7];
	bool hasWon();
};

