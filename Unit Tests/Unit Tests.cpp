#include "pch.h"
#include "CppUnitTest.h"
#include "../Marble Solitaire/board_configuration.h"
#include "../Marble Solitaire/difficulty.h"
#include "../Marble Solitaire/game.h"
#include "../Marble Solitaire/move.h"
#include <vector>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(BoardInitialisation)
		{
			std::vector<std::vector<int>> board = {
				{-1, -1, 1, 1, 1, -1, -1},
				{-1, -1, 1, 1, 1, -1, -1},
				  {1, 1, 1, 1, 1, 1, 1},
				  {1, 1, 1, 0, 1, 1, 1},
				  {1, 1, 1, 1, 1, 1, 1},
				{-1, -1, 1, 1, 1, -1, -1},
				{-1, -1, 1, 1, 1, -1, -1},
			};
			Game game(board, DIFFICULTY::EASY);

			for (int i = 0; i < board.size(); i++) {
				for (int j = 0; j < board[i].size(); j++) {
					std::vector<std::vector<int>> gameBoard = *game.getBoard();
					Assert::AreEqual(board[i][j], gameBoard[i][j]);
					Logger::WriteMessage((std::to_string(gameBoard[i][j]) + " ").c_str());
				}
				Logger::WriteMessage("\n");
			}
		}
		TEST_METHOD(PerformMoveValidMoves)
		{
			std::vector<std::vector<int>> board = {
				{-1, -1, 1, 1, 1, -1, -1},
				{-1, -1, 1, 1, 1, -1, -1},
					{1, 1, 1, 1, 1, 1, 1},
					{1, 1, 1, 0, 1, 1, 1},
					{1, 1, 1, 1, 1, 1, 1},
				{-1, -1, 1, 1, 1, -1, -1},
				{-1, -1, 1, 1, 1, -1, -1},
			};
			Game game(board, DIFFICULTY::EASY);

			game.performMove(Move(make_pair(3, 1), make_pair(3, 3)));
			game.performMove(Move(make_pair(1, 2), make_pair(3, 2)));
			game.performMove(Move(make_pair(4, 2), make_pair(2, 2)));
			game.performMove(Move(make_pair(3, 4), make_pair(3, 2)));
			game.performMove(Move(make_pair(5, 4), make_pair(3, 4)));
			game.performMove(Move(make_pair(4, 6), make_pair(4, 4)));
			game.performMove(Move(make_pair(3, 4), make_pair(5, 4)));
			game.performMove(Move(make_pair(2, 6), make_pair(4, 6)));
			game.performMove(Move(make_pair(2, 5), make_pair(4, 5)));
			game.performMove(Move(make_pair(4, 6), make_pair(4, 4)));
			game.performMove(Move(make_pair(1, 4), make_pair(1, 2)));
			game.performMove(Move(make_pair(6, 2), make_pair(4, 2)));
			game.performMove(Move(make_pair(5, 4), make_pair(3, 4)));
			game.performMove(Move(make_pair(6, 4), make_pair(6, 2)));
			game.performMove(Move(make_pair(3, 2), make_pair(5, 2)));
			game.performMove(Move(make_pair(6, 2), make_pair(4, 2)));
			game.performMove(Move(make_pair(5, 3), make_pair(3, 3)));
			game.performMove(Move(make_pair(3, 3), make_pair(1, 3)));
			game.performMove(Move(make_pair(3, 4), make_pair(1, 4)));
			game.performMove(Move(make_pair(0, 3), make_pair(2, 3)));
			game.performMove(Move(make_pair(0, 4), make_pair(2, 4)));
			game.performMove(Move(make_pair(1, 2), make_pair(3, 2)));
			game.performMove(Move(make_pair(2, 4), make_pair(2, 2)));
			game.performMove(Move(make_pair(3, 2), make_pair(1, 2)));
			game.performMove(Move(make_pair(0, 2), make_pair(2, 2)));
			game.performMove(Move(make_pair(2, 1), make_pair(2, 3)));
			game.performMove(Move(make_pair(4, 1), make_pair(4, 3)));

			std::vector<std::vector<int>> expectedBoard = {
				{-1, -1, 0, 0, 0, -1, -1},
				{-1, -1, 0, 0, 0, -1, -1},
					{1, 0, 0, 1, 0, 0, 0},
					{1, 0, 0, 0, 0, 0, 0},
					{1, 0, 0, 1, 0, 0, 0},
				{-1, -1, 0, 0, 0, -1, -1},
				{-1, -1, 0, 0, 0, -1, -1},
			};

			std::vector<std::vector<int>> gameBoard = *game.getBoard();

			for (int i = 0; i < board.size(); i++) {
				for (int j = 0; j < board[i].size(); j++) {
					Assert::AreEqual(expectedBoard[i][j], gameBoard[i][j]);
				}
			}
		}
		TEST_METHOD(PerformMoveInvalidMoves)
		{
			std::vector<std::vector<int>> board = {
				{-1, -1, 1, 1, 1, -1, -1},
				{-1, -1, 1, 1, 1, -1, -1},
				  {1, 1, 1, 1, 1, 1, 1},
				  {1, 1, 1, 0, 1, 1, 1},
				  {1, 1, 1, 1, 1, 1, 1},
				{-1, -1, 1, 1, 1, -1, -1},
				{-1, -1, 1, 1, 1, -1, -1},
			};
			Game game(board, DIFFICULTY::EASY);

			game.performMove(Move(make_pair(3, 1), make_pair(3, 3)));
			game.performMove(Move(make_pair(1, 2), make_pair(3, 2)));
			game.performMove(Move(make_pair(4, 2), make_pair(2, 2)));
			game.performMove(Move(make_pair(3, 4), make_pair(3, 2)));
			game.performMove(Move(make_pair(5, 4), make_pair(3, 4)));

			// Invalid move
			game.performMove(Move(make_pair(-10, 4), make_pair(3, 4)));

			game.performMove(Move(make_pair(4, 6), make_pair(4, 4)));
			game.performMove(Move(make_pair(3, 4), make_pair(5, 4)));

			// Invalid moves
			game.performMove(Move(make_pair(3, 4), make_pair(5, 4)));
			game.performMove(Move(make_pair(3, 4), make_pair(5, 4)));

			game.performMove(Move(make_pair(2, 6), make_pair(4, 6)));
			game.performMove(Move(make_pair(2, 5), make_pair(4, 5)));
			game.performMove(Move(make_pair(4, 6), make_pair(4, 4)));
			game.performMove(Move(make_pair(1, 4), make_pair(1, 2)));

			// Invalid moves
			game.performMove(Move(make_pair(0, 0), make_pair(0, 2)));
			game.performMove(Move(make_pair(0, 6), make_pair(1, 6)));
			game.performMove(Move(make_pair(6, 6), make_pair(6, 6)));
			game.performMove(Move(make_pair(6, 0), make_pair(6, 2)));

			game.performMove(Move(make_pair(6, 2), make_pair(4, 2)));
			game.performMove(Move(make_pair(5, 4), make_pair(3, 4)));
			game.performMove(Move(make_pair(6, 4), make_pair(6, 2)));
			game.performMove(Move(make_pair(3, 2), make_pair(5, 2)));
			game.performMove(Move(make_pair(6, 2), make_pair(4, 2)));
			game.performMove(Move(make_pair(5, 3), make_pair(3, 3)));
			game.performMove(Move(make_pair(3, 3), make_pair(1, 3)));
			game.performMove(Move(make_pair(3, 4), make_pair(1, 4)));
			game.performMove(Move(make_pair(0, 3), make_pair(2, 3)));
			game.performMove(Move(make_pair(0, 4), make_pair(2, 4)));
			game.performMove(Move(make_pair(1, 2), make_pair(3, 2)));
			game.performMove(Move(make_pair(2, 4), make_pair(2, 2)));
			game.performMove(Move(make_pair(3, 2), make_pair(1, 2)));
			game.performMove(Move(make_pair(0, 2), make_pair(2, 2)));
			game.performMove(Move(make_pair(2, 1), make_pair(2, 3)));
			game.performMove(Move(make_pair(4, 1), make_pair(4, 3)));

			std::vector<std::vector<int>> expectedBoard = {
				{-1, -1, 0, 0, 0, -1, -1},
				{-1, -1, 0, 0, 0, -1, -1},
				  {1, 0, 0, 1, 0, 0, 0},
				  {1, 0, 0, 0, 0, 0, 0},
				  {1, 0, 0, 1, 0, 0, 0},
				{-1, -1, 0, 0, 0, -1, -1},
				{-1, -1, 0, 0, 0, -1, -1},
			};

			std::vector<std::vector<int>> gameBoard = *game.getBoard();

			for (int i = 0; i < board.size(); i++) {
				for (int j = 0; j < board[i].size(); j++) {
					Assert::AreEqual(expectedBoard[i][j], gameBoard[i][j]);
				}
			}
		}
		TEST_METHOD(MovesCounter)
		{
			std::vector<std::vector<int>> board = {
				{-1, -1, 1, 1, 1, -1, -1},
				{-1, -1, 1, 1, 1, -1, -1},
				  {1, 1, 1, 1, 1, 1, 1},
				  {1, 1, 1, 0, 1, 1, 1},
				  {1, 1, 1, 1, 1, 1, 1},
				{-1, -1, 1, 1, 1, -1, -1},
				{-1, -1, 1, 1, 1, -1, -1},
			};
			Game game(board, DIFFICULTY::EASY);

			game.performMove(Move(make_pair(3, 1), make_pair(3, 3)));
			game.performMove(Move(make_pair(1, 2), make_pair(3, 2)));
			game.performMove(Move(make_pair(4, 2), make_pair(2, 2)));
			game.performMove(Move(make_pair(3, 4), make_pair(3, 2)));
			game.performMove(Move(make_pair(5, 4), make_pair(3, 4)));

			// Invalid move
			game.performMove(Move(make_pair(-10, 4), make_pair(3, 4)));

			game.performMove(Move(make_pair(4, 6), make_pair(4, 4)));
			game.performMove(Move(make_pair(3, 4), make_pair(5, 4)));

			// Invalid moves
			game.performMove(Move(make_pair(3, 4), make_pair(5, 4)));
			game.performMove(Move(make_pair(3, 4), make_pair(5, 4)));

			game.performMove(Move(make_pair(2, 6), make_pair(4, 6)));
			game.performMove(Move(make_pair(2, 5), make_pair(4, 5)));
			game.performMove(Move(make_pair(4, 6), make_pair(4, 4)));
			game.performMove(Move(make_pair(1, 4), make_pair(1, 2)));

			// Invalid moves
			game.performMove(Move(make_pair(0, 0), make_pair(0, 2)));
			game.performMove(Move(make_pair(0, 6), make_pair(1, 6)));
			game.performMove(Move(make_pair(6, 6), make_pair(6, 6)));
			game.performMove(Move(make_pair(6, 0), make_pair(6, 2)));

			game.performMove(Move(make_pair(6, 2), make_pair(4, 2)));
			game.performMove(Move(make_pair(5, 4), make_pair(3, 4)));
			game.performMove(Move(make_pair(6, 4), make_pair(6, 2)));
			game.performMove(Move(make_pair(3, 2), make_pair(5, 2)));
			game.performMove(Move(make_pair(6, 2), make_pair(4, 2)));
			game.performMove(Move(make_pair(5, 3), make_pair(3, 3)));
			game.performMove(Move(make_pair(3, 3), make_pair(1, 3)));
			game.performMove(Move(make_pair(3, 4), make_pair(1, 4)));
			game.performMove(Move(make_pair(0, 3), make_pair(2, 3)));
			game.performMove(Move(make_pair(0, 4), make_pair(2, 4)));
			game.performMove(Move(make_pair(1, 2), make_pair(3, 2)));
			game.performMove(Move(make_pair(2, 4), make_pair(2, 2)));
			game.performMove(Move(make_pair(3, 2), make_pair(1, 2)));
			game.performMove(Move(make_pair(0, 2), make_pair(2, 2)));
			game.performMove(Move(make_pair(2, 1), make_pair(2, 3)));
			game.performMove(Move(make_pair(4, 1), make_pair(4, 3)));

			unsigned int moves = 27;

			Logger::WriteMessage((std::to_string(*game.getMovesCounter()).c_str()));
			Assert::AreEqual(moves, *game.getMovesCounter());
		}
		TEST_METHOD(HasGameFinished)
		{
			std::vector<std::vector<int>> board = {
				{-1, -1, 1, 1, 1, -1, -1},
				{-1, -1, 1, 1, 1, -1, -1},
					{1, 1, 1, 1, 1, 1, 1},
					{1, 1, 1, 0, 1, 1, 1},
					{1, 1, 1, 1, 1, 1, 1},
				{-1, -1, 1, 1, 1, -1, -1},
				{-1, -1, 1, 1, 1, -1, -1},
			};
			Game game(board, DIFFICULTY::EASY);

			vector<Move> moves = {
				(Move(make_pair(3, 1), make_pair(3, 3))),
				(Move(make_pair(1, 2), make_pair(3, 2))),
				(Move(make_pair(4, 2), make_pair(2, 2))),
				(Move(make_pair(3, 4), make_pair(3, 2))),
				(Move(make_pair(5, 4), make_pair(3, 4))),
				(Move(make_pair(4, 6), make_pair(4, 4))),
				(Move(make_pair(3, 4), make_pair(5, 4))),
				(Move(make_pair(2, 6), make_pair(4, 6))),
				(Move(make_pair(2, 5), make_pair(4, 5))),
				(Move(make_pair(4, 6), make_pair(4, 4))),
				(Move(make_pair(1, 4), make_pair(1, 2))),
				(Move(make_pair(6, 2), make_pair(4, 2))),
				(Move(make_pair(5, 4), make_pair(3, 4))),
				(Move(make_pair(6, 4), make_pair(6, 2))),
				(Move(make_pair(3, 2), make_pair(5, 2))),
				(Move(make_pair(6, 2), make_pair(4, 2))),
				(Move(make_pair(5, 3), make_pair(3, 3))),
				(Move(make_pair(3, 3), make_pair(1, 3))),
				(Move(make_pair(3, 4), make_pair(1, 4))),
				(Move(make_pair(0, 3), make_pair(2, 3))),
				(Move(make_pair(0, 4), make_pair(2, 4))),
				(Move(make_pair(1, 2), make_pair(3, 2))),
				(Move(make_pair(2, 4), make_pair(2, 2))),
				(Move(make_pair(3, 2), make_pair(1, 2))),
				(Move(make_pair(0, 2), make_pair(2, 2))),
				(Move(make_pair(2, 1), make_pair(2, 3))),
			};

			for (Move move : moves) {
				game.performMove(move);
				Assert::IsFalse(game.hasFinished());
			}

			game.performMove(Move(make_pair(4, 1), make_pair(4, 3)));
			Assert::IsTrue(game.hasFinished());
		}
		TEST_METHOD(HasWon)
		{
			std::vector<std::vector<int>> board = {
				{-1, -1, 1, 1, 1, -1, -1},
				{-1, -1, 1, 1, 1, -1, -1},
					{1, 1, 1, 1, 1, 1, 1},
					{1, 1, 1, 0, 1, 1, 1},
					{1, 1, 1, 1, 1, 1, 1},
				{-1, -1, 1, 1, 1, -1, -1},
				{-1, -1, 1, 1, 1, -1, -1},
			};

			Game game(board, DIFFICULTY::EASY);

			vector<Move> moves = {
				(Move(make_pair(3, 1), make_pair(3, 3))),
				(Move(make_pair(1, 2), make_pair(3, 2))),
				(Move(make_pair(4, 2), make_pair(2, 2))),
				(Move(make_pair(3, 4), make_pair(3, 2))),
				(Move(make_pair(5, 4), make_pair(3, 4))),
				(Move(make_pair(4, 6), make_pair(4, 4))),
				(Move(make_pair(3, 4), make_pair(5, 4))),
				(Move(make_pair(2, 6), make_pair(4, 6))),
				(Move(make_pair(2, 5), make_pair(4, 5))),
				(Move(make_pair(4, 6), make_pair(4, 4))),
				(Move(make_pair(1, 4), make_pair(1, 2))),
				(Move(make_pair(6, 2), make_pair(4, 2))),
				(Move(make_pair(5, 4), make_pair(3, 4))),
				(Move(make_pair(6, 4), make_pair(6, 2))),
				(Move(make_pair(3, 2), make_pair(5, 2))),
				(Move(make_pair(6, 2), make_pair(4, 2))),
				(Move(make_pair(5, 3), make_pair(3, 3))),
				(Move(make_pair(3, 3), make_pair(1, 3))),
				(Move(make_pair(3, 4), make_pair(1, 4))),
				(Move(make_pair(0, 3), make_pair(2, 3))),
				(Move(make_pair(0, 4), make_pair(2, 4))),
				(Move(make_pair(1, 2), make_pair(3, 2))),
				(Move(make_pair(2, 4), make_pair(2, 2))),
				(Move(make_pair(3, 2), make_pair(1, 2))),
				(Move(make_pair(0, 2), make_pair(2, 2))),
				(Move(make_pair(2, 1), make_pair(2, 3))),
				(Move(make_pair(4, 1), make_pair(4, 3)))
			};

			for (Move move : moves) {
				game.performMove(move);
			}

			Assert::IsFalse(game.hasWon());
		}
	};
}
