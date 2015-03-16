// King.h

#ifndef KING_H
#define KING_H

#include "Piece.h"

/**
* This class represents a king in a chess game.
*/
class King : public Piece
{

public:

	/**
	* A constructor.
	* Creates new king. sends the value to the piece (base) class.
	* More info in piece.h constructor.
	*/
	King(Point& p, Piece::Color c, Board* b);

	/**
	* Destructor.
	*/
	~King();

	/**
	* This method overloading the one in piece class.
	* Moves a king after the checks were made and taking care of king moves as castle.
	* Updates the rook to complete the castling.
	* @param Point.
	*/
	void tryToMove(Point p);

protected:

	/**
	* Checks specific move legality for king.
	* @param p - point to check to move to.
	* @return the type of the move.
	*/
	MoveType canMove(Point p);

private:

	bool _moved;

};

#endif
