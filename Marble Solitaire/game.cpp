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
bool Game::move(Move move) {
    // Extract origin and destination coordinates from the move
    int originY = move.getOrigin().first;
    int originX = move.getOrigin().second;
    int destY = move.getDestination().first;
    int destX = move.getDestination().second;

    /**
    Check if the move is valid
    - distance equal to abs(2)
    - move only horizontally and vertically, not diagonally 
    */
    int dY = destY - originY;
    int dX = destX - originX;
    if ((dX != 0 && dY != 0) || abs(dX) != 2 || abs(dY) != 2) {
        return false;
    }

    // Check if there's a marble at the origin and an empty space at the destination
    // 1 - piece, 0 - space, -1 - wall
    int originValue = board[originY][originX];
    int middleValue = board[originY + dY / 2][originX + dX / 2];
    int destinationValue = board[destY][destX];
    if (originValue != 1 || middleValue != 1 || destinationValue != 0) {
        return false;
    }

    // Perform the move
    board[destY][destX] = 1;
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
	return false;
}