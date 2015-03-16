// Bishop.h

#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

/**
* This class represents a bishop in a chess game.
*/
class Bishop : public Piece
{

public:

	/**
	* A constructor.
	* Creates new bishop. sends the value to the piece (base) class.
	* More info in piece.h constructor.
	*/
	Bishop(Point p, Piece::Color c, Board* b);

	/**
	 * Destructor.
	 */
	~Bishop();

protected:

	/**
	* Checks specific move legality for bishop.
	* @param p - point to check to move to.
	* @return the type of the move.
	*/
	MoveType canMove(Point p);

private:

	// updates the index according to the positions.
	void updateIndex(int& x, int& y, Point p);

};

#endif
