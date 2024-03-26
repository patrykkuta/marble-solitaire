#include "game.h"
#include <iostream>

Game::Game(const std::vector<std::vector<int>>& configuration, DIFFICULTY difficulty) {
    // Initialize the board as a 2D vector of size 7x7
    board.resize(7, std::vector<int>(7));

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			this->board[i][j] = configuration[i][j];
			std::cout << board[i][j] << " ";
		}

		std::cout << std::endl;
	}
	std::cout << std::endl;

	this->difficulty = difficulty;
}
std::vector<std::vector<int>>* Game::getBoard() {
	return &board;
}
std::stack<Move>* Game::getRecentMoves() {
	return &recentMoves;
}
unsigned int* Game::getMovesCounter() {
	return &movesCounter;
}
bool Game::performMove(Move move) {
    // Extract origin and destination coordinates from the move
    int originY = move.getOrigin().first;
    int originX = move.getOrigin().second;
    int destinationY = move.getDestination().first;
    int destinationX = move.getDestination().second;

    if (!isMoveValid(originY, originX, destinationY, destinationX)) return false;

    int dY = destinationY - originY;
    int dX = destinationX - originX;

    // Perform the move
    board[destinationY][destinationX] = 1;
    board[originY][originX] = 0;
    board[originY + dY / 2][originX + dX / 2] = 0;

    // Store the recent move
    recentMoves.push(move);
    movesCounter++;

    return true;
}
void Game::undoMove() {
    if (!recentMoves.empty()) recentMoves.pop();
}
std::queue<Move> Game::solve() {
	// Implement solve
	std::queue<Move> solution;
	return solution;
}
Move Game::getHint() {
	// Return next move, run some algorithm to find the move
	std::pair<short, short> origin = std::make_pair(0, 0);
	std::pair<short, short> destination = std::make_pair(0, 0);
	Move move(origin, destination);
	return move;
}
bool Game::hasWon() {
    bool alreadyPresent = false;
    bool isMiddle = false;

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == 1) {
                if (alreadyPresent) return false;
                alreadyPresent = true;

                isMiddle = (i == 3 && j == 3);
            }
            
        }
    }

    if ((difficulty == DIFFICULTY::EASY) || (difficulty == DIFFICULTY::HARD && isMiddle)) return true;
    else return false;
}

bool Game::hasFinished() {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == 1) {
                if ((i + 2 < 7 && board[i + 1][j] == 1 && board[i + 2][j] == 0) ||
                    (i - 2 >= 0 && board[i - 1][j] == 1 && board[i - 2][j] == 0) ||
                    (j + 2 < 7 && board[i][j + 1] == 1 && board[i][j + 2] == 0) ||
                    (j - 2 >= 0 && board[i][j - 1] == 1 && board[i][j - 2] == 0)) {
                    return false;  // A move is possible, game not finished
                }
            }
        }
    }

    return true;
}
	return false;
}