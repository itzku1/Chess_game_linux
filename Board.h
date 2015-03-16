// Board.h

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

// WIDTH = HEIGHT = 8
const int WIDTH = 8;
const int PLAYERS = 2;
// for print in the board.
const std::string LETTERS = "  ABCDEFGH";

/**
 * This class represents the board game. This class responsible to all the interaction with 
 * the board- get the peice from a point, place and replace it, moves the pieces on it,
 * looking for checks, checkmate and remember data if need as in en passant move.
 * The distribution between the board and piece - piece responsible to all the checks
 * and the board for the interaction without any checks.
 */
class Board
{

public:

	/**
	 * A constructor.
	 * Construct new game board with all the pieces in the start positions.
	 * Each point in the board is a pointer to Piece or null pointer for empty points.
	 * Holds the current player color which is the one that plays now, and en - passant point
	 * (0,0) by default if a pawn made a double step.
	 */
	Board();

	/**
	 * Destructor.
	 */
	~Board();

	/**
	 * Returns the piece at the given point in the board or null pointer for empty point.
	 * @param Point to find.
	 * @return pointer to piece at the given point.
	 */
	Piece* pieceAt(Point p);

	/**
	 * Returns the piece at the given (x,y) in the board or null pointer for empty point.
	 * @param x,y coordinates to find.
	 * @return pointer to piece at the given coordinates.
	 */
	Piece* pieceAt(int x, int y);

	/**
	 * Place a piece on a given point on the board.
	 * @param p - pointer to the piece to be place.
	 * @param pt - pointer to the point on the board.
	 */
	void placePieceAt(Piece* p, Point* pt);

	/**
	 * Switch turn between players.
	 */
	void move();

	/**
	 * Moves piece from p1 which is the piece location to p2 without any checks.
	 * sends default point to en - passant becouse no double step where made.
	 * @param p1 - point of the current location of piece.
	 * @param p2 - point to move a piece to.
	 */
	void move(Point p1, Point p2);

	/**
	 * Moves piece from p1 which is the piece location to p2 without any checks.
	 * Records the point of en - passant.
	 * @param p1 - point of the current location of piece.
	 * @param p2 - point to move a piece to.
	 * @param enP - the point recorded to en - passant move if one will occure.
	 */
	void move(Point p1, Point p2, Point enP);

	/**
	 * Sends the points to check if the move can be done using the methods of the derive classes.
	 * If the move is legal, moves it.
	 * @param p1 - point of the current location of piece.
	 * @param p2 - point to move a piece to.
	 */
	void tryToMove(Point p1, Point p2);

	/**
	 * Returns the current player color.
	 * @return int.
	 */
	int getTurn();

	/**
	 * The board always holds the kings positions.
	 * This method sets new king position of the current player if move with the king were made.
	 * @param p - point of the king location.
	 */
	void setKingPos(Point p);

	/**
	 * Returns the record of move to check for en - passant.
	 * @return Point.
	 */
	Point getEnPassant();

	/**
	 * Returns true if the current player is in check or false if not.
	 * @return boolean.
	 */
	bool check();

	/**
	 * Returns true if the current player is in checkmate or false if not.
	 * @return boolean.
	 */
	bool checkmate();

	/**
	 * Prints the board.
	 */
	void printBoard();

	/**
	 * Delete all remain pieces on the board at the end of the game.
	 */
	void deleteBoard();

private:

	Piece* _myBoard[WIDTH][WIDTH];

	Point _kingsPos[PLAYERS];
	
	int _turn;

	Point _enPassant;

};

#endif
