// Knight.h

#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

/**
* This class represents a knight in a chess game.
*/
class Knight : public Piece
{

public:

	/**
	* A constructor.
	* Creates new knight. sends the value to the piece (base) class.
	* More info in piece.h constructor.
	*/
	Knight(Point p, Piece::Color c, Board* b);

	/**
	* Destructor.
	*/
	~Knight();

protected:

	/**
	* Checks specific move legality for knight.
	* @param p - point to check to move to.
	* @return the type of the move.
	*/
	MoveType canMove(Point p);

};

#endif
