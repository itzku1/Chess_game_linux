// chess.h

#ifndef CHESS_H_
#define CHESS_H_

#include "Board.h"

using namespace std;
/**
 * This class starts and run the game.
 * Responsible to get the input from the users annalyze it and acts the correct moves.
 */
class Chess
{

public:
	
	/**
	 * Initializes and starts new game.
	 */
	Chess();

	/**
	 * Destructor.
	 */
	~Chess();

	/**
	 * Sets player 1 name.
	 * @param string name.
	 */
	void setP1Name(string name);

	/**
	 * Sets player 2 name.
	 * @param string name.
	 */
	void setP2Name(string name);

	/**
	 * Returns the game board.
	 * @return board pointer.
	 */
	Board* getBoard();

	/**
	 * Returns player name.
	 * @return string.
	 */
	string getName();

	/**
	 * Returns the winner name.
	 * @return string.
	 */
	string getWinner();

	/**
	 * Checks the legality of the input (not in terms of moves legality).
	 * @param move - represents two point to move between them.
	 * @returns true if the input is legal or false otherwise.
	 */
	bool checkInput(string move);

private:

	Board* _game;
	string _pNames[PLAYERS];
	
};

#endif
