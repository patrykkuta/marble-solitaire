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

	bool isMoveValid(int originY, int originX, int destinationY, int destinationX);
public:
	Game(const std::vector<std::vector<int>>& configuration, DIFFICULTY difficulty);
	std::vector<std::vector<int>>* getBoard();
	std::stack<Move>* getRecentMoves();
	unsigned int* getMovesCounter();
	bool performMove(Move move);
	void undoMove();
	std::queue<Move> solve();
	Move getHint();
	bool hasWon();
	bool hasFinished();
	void setDifficulty(DIFFICULTY difficulty);
};

