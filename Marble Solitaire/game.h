#pragma once
#include <stack>
#include <queue>
#include "board_configuration.h"
#include "difficulty.cpp"
#include "board.h"
#include "move.h"

class Game {
private:
	Board board;
	std::stack<Move> recentMoves;
	unsigned int movesCounter;
	bool hasFinished;
public:
	Game(BOARD_CONFIGURATION configuration, DIFFICULTY difficulty);
	Board getBoard();
	std::stack<Move> getRecentMoves();
	unsigned int getMovesCounter();
	bool finishGame();
	bool move(Move move);
	std::queue<Move> solve();
	Move getHint();
};

