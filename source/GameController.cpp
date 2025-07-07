#include "GameController.h"
#include "ScreenManager.h"
#include "EndGameScreen.h"

using namespace std;

bool GameController::hasWon = false;
bool GameController::hasFinished = false;

GameController::GameController() {}

void GameController::newGame(const std::vector<std::vector<int>>& configuration, DIFFICULTY difficulty) {
	if (game != nullptr) delete game;

	GameController::hasWon = false;
	GameController::hasFinished = false;

	game = new Game(configuration, difficulty);
}

GameController::~GameController() {
	if (game != nullptr) delete game;
}

bool GameController::move() {
	Move move(selectedMarble, selectedEmptySpace);
	bool hasMoved = game->performMove(move);

	if (hasMoved) {
		if (game->hasFinished()) {
			GameController::hasFinished = true;
			GameController::hasWon = game->hasWon();
		}
	}



	return hasMoved;
}

vector<vector<int>>* GameController::getBoard() {
	return game->getBoard();
}

void GameController::setMarble(pair<short, short> marble) { this->selectedMarble = marble; }
void GameController::setEmptySpace(pair<short, short> emptySpace) { this->selectedEmptySpace = emptySpace; }
pair<short, short> GameController::getMarble() { return selectedMarble; }
pair<short, short> GameController::getEmptySpace() { return selectedEmptySpace; }