// chess.cpp

#include "chess.h"

using namespace std;

// input legal length value.
const int INPUT_LENGTH = 4;
// ascii value of 'A' to convert and check input legality.
const int ASCII_A = 65;
// ascii value of '8' to convert and check input legality.
const int ASCII_8 = 56;

Chess::Chess()
{
	_game = new Board();
	_pNames[0] = "";
	_pNames[1] = "";
}

Chess::~Chess()
{
	delete _game;
}

void Chess::setP1Name(string name)
{
	_pNames[0] += name;
}

void Chess::setP2Name(string name)
{
	_pNames[1] += name;
}

string Chess::getName()
{
	return _pNames[_game->getTurn()];
}

string Chess::getWinner()
{
	return _pNames[1 - _game->getTurn()];
}

Board* Chess::getBoard()
{
	return _game;
}

bool Chess::checkInput(string move)
{
	if (move.length() != INPUT_LENGTH)
	{
		return false;
	}
	return true;
}

int main()
{
	// create new game
	Chess* game = new Chess();
	string name;

	// get player 1 name.
	cout << "Enter white player name:" << endl;
	cin >> name;
	game->setP1Name(name);

	// get player 2 name.
	cout << "Enter black player name:" << endl;
	cin >> name;
	game->setP2Name(name);

	// run turns while there is no checkmate.
	while (!(game->getBoard()->checkmate()))
	{
		cout << "\33[2J";

		// print the board.
		game->getBoard()->printBoard();
		cout << endl;

		// print check if needed.
		if (game->getBoard()->check())
		{
			cout << "\33[37;41mCheck!\33[0m" << endl;
		}

		// get the next move.
		string move;
		cout << game->getName() << ": Please enter your move:" << endl;
		cin >> move;

		// check validation.
		if (game->checkInput(move))
		{
			Point p1(abs((int)move[1] - ASCII_8), (int)move[0] - ASCII_A);
			Point p2(abs((int)move[3] - ASCII_8), (int)move[2] - ASCII_A);

			// move the piece if everything is O.K
			game->getBoard()->tryToMove(p1, p2);
		}
		else
		{
			cout << "\33[37;41millegal move\33[0m" << endl;
		}
	}

	cout << "\33[2J";
	game->getBoard()->printBoard();

	// prints the winner.
	cout << game->getWinner() << " won!" << endl;

	// clean board.
	game->getBoard()->deleteBoard();
	delete game;
}
