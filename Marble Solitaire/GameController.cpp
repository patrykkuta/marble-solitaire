#include "GameController.h"

using namespace std;

GameController::GameController() {}

Game* GameController::newGame(const std::vector<std::vector<int>>& configuration, DIFFICULTY difficulty) {
	game = new Game(configuration, difficulty);
	return game;
}

GameController::~GameController() {
	delete game;
}

bool GameController::move() {
	// Take the selected marble
	// Take the selected space
	// Construct a Move object with marble and space coordinates converted to array indices of the board
	// Call the game.performMove(move) to perform the move and return the value the method returns
	return true;
}

vector<vector<int>>* GameController::getBoard() {
	return game->getBoard();
}

void GameController::setMarble(GLuint marble) { this->selectedMarble = marble; }
void GameController::setEmptySpace(GLuint emptySpace) { this->selectedEmptySpace = emptySpace; }