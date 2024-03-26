#include <iostream>
#include "board_configuration.h"
#include "difficulty.h"
#include "GameController.h"

using namespace std;

int main() {

	GameController gcontroller;
	Game* game = gcontroller.newGame(BOARD_CONFIGURATION::CROSS, DIFFICULTY::EASY);

	while (!game->hasFinished()) {
		std::vector<std::vector<int>> gameBoard = *game->getBoard();

		for (int i = 0; i < gameBoard.size(); i++) {
			for (int j = 0; j < gameBoard[i].size(); j++) {
				cout << gameBoard[i][j] << " ";
			}
			cout << endl;
		}

		cout << endl;

		int oX, oY, dX, dY;

		cout << "Enter origin move coordinates and destination move coordinates e.g. 2 4 4 4: ";
		cin >> oX >> oY >> dX >> dY;
		cout << endl;

		game->performMove(Move(make_pair(oX, oY), make_pair(dX, dY)));
	}

	if (game->hasWon()) {
		cout << "Congratulations! You won!" << endl;
	}
	else {
		cout << "Better luck next time!" << endl;
	}

	delete game;
	return 0;
}