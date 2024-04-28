#include "GameController.h"

using namespace std;

GameController::GameController() {}

Game* GameController::newGame(const std::vector<std::vector<int>>& configuration, DIFFICULTY difficulty) {
	if (game != nullptr) delete game;

	game = new Game(configuration, difficulty);
	return game;
}

GameController::~GameController() {
	if (game != nullptr) delete game;
}

bool GameController::move() {
	Move move(selectedMarble, selectedEmptySpace);
	bool moved = game->performMove(move);

	if (game->hasFinished()) {
		delete game;
		game = new Game(BOARD_CONFIGURATION::PLUS, DIFFICULTY::EASY);
	}

	return moved;
}

vector<vector<int>>* GameController::getBoard() {
	return game->getBoard();
}

void GameController::setMarble(pair<short, short> marble) { this->selectedMarble = marble; }
void GameController::setEmptySpace(pair<short, short> emptySpace) { this->selectedEmptySpace = emptySpace; }
pair<short, short> GameController::getMarble() { return selectedMarble; }
pair<short, short> GameController::getEmptySpace() { return selectedEmptySpace; }