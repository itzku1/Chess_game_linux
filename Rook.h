// Rook.h

#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

/**
* This class represents a rook in a chess game.
*/
class Rook : public Piece
{

public:

	/**
	* A constructor.
	* Creates new rook. sends the value to the piece (base) class.
	* More info in piece.h constructor.
	*/
	Rook(Point& p, Piece::Color c, Board* b);

	/**
	* Destructor.
	*/
	~Rook();

	/**
	 * Returns true if the rook mooved already and false otherwise.
	 * @return boolean.
	 */
	bool getMoved();

	/**
	* This method overloading the one in piece class.
	* Moves a rook after the checks were made and taking care of rook moves.
	* Update the moved of rook to avoid castle after the rook moved.
	* @param Point.
	*/
	void tryToMove(Point p);

protected:

	/**
	* Checks specific move legality for rook.
	* @param p - point to check to move to.
	* @return the type of the move.
	*/
	MoveType canMove(Point p);

private:

	// updates the index according to the positions.
	void updateIndex(int& i, Point p);

	bool _moved;

};

#endif
