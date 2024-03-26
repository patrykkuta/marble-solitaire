#include "GameController.h"

GameController::GameController() {}

Game* GameController::newGame(const std::vector<std::vector<int>>& configuration, DIFFICULTY difficulty) {
	return new Game(configuration, difficulty);
}