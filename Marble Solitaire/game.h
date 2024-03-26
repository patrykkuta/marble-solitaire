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
	std::stack<Move> recentMoves;
	unsigned int movesCounter = 0;
	unsigned int difficulty;

public:
	Game(int(&configuration)[7][7], DIFFICULTY difficulty);
	auto getBoard() -> int(*)[7];
	std::stack<Move>* getRecentMoves();
	unsigned int* getMovesCounter();
	bool move(Move move);
	void undoMove();
	std::queue<Move> solve();
	Move getHint();
	bool hasWon();
	void setDifficulty(DIFFICULTY difficulty);
};

