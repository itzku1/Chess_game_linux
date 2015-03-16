// Pawn.h

#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

/**
 * This class represents a pawn in a chess game.
 */
class Pawn : public Piece
{

public:

	/**
	 * A constructor.
	 * Creates new pawn. sends the value to the piece (base) class.
	 * More info in piece.h constructor.
	 */
	Pawn(Point p, Piece::Color c, Board* b);

	/**
	 * Destructor.
	 */
	~Pawn();

	/**
	 * This method overloading the one in piece class.
	 * Moves a pawn after the checks were made and taking care of pawn moves as double step
	 * and en - passant.
	 * @param Point.
	 */
	void tryToMove(Point p);

protected:

	/**
	 * Checks specific move legality for pawn.
	 * @param p - point to check to move to.
	 * @return the type of the move.
	 */
	MoveType canMove(Point p);
	
private:

	int _direction;

	bool _moved;

};

#endif
