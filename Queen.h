// Queen.h

#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

/**
* This class represents a queen in a chess game.
*/
class Queen : public Piece
{

public:

	/**
	* A constructor.
	* Creates new queen. sends the value to the piece (base) class.
	* More info in piece.h constructor.
	*/
	Queen(Point& p, Piece::Color c, Board* b);

	/**
	* Destructor.
	*/
	~Queen();

protected:

	/**
	* Checks specific move legality for queen.
	* @param p - point to check to move to.
	* @return the type of the move.
	*/
	MoveType canMove(Point p);

private:

	// updates the index according to the positions.
	void updateIndex(int& i, Point p);

	// updates the index according to the positions.
	void updateIndex(int& x, int& y, Point p);

};

#endif
