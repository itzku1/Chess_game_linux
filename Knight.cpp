// Knight.cpp

#include "Knight.h"

Knight::Knight(Point p, Piece::Color c, Board* b) : Piece(p, c, b, KNIGHT)
{}

Knight::~Knight()
{}

Piece::MoveType Knight::canMove(Point p)
{
	if (Piece::canMove(p) == ILLEGAL)
	{
		return ILLEGAL;
	}

	int dx = getLocation().getX() - p.getX();
	int dy = getLocation().getY() - p.getY();

	if (abs(dx) * abs(dy) == 2)
	{
		return NORMAL;
	}
	return ILLEGAL;
}
