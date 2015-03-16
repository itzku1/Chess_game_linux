// Pawn.cpp

#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(Point p, Piece::Color c, Board* b) : Piece(p, c, b, PAWN)
{
	_moved = false;

	if (c == WHITE)
		_direction = 1;
	else
		_direction = -1;
}

Pawn::~Pawn()
{}

Piece::MoveType Pawn::canMove(Point p)
{
	if (Piece::canMove(p) == ILLEGAL)
	{
		return ILLEGAL;
	}
	if ((getBoard()->getEnPassant().getX() != 0 && getBoard()->getEnPassant().getX() != 0)
		&& getBoard()->getEnPassant().getX() == p.getX()
		&& getBoard()->getEnPassant().getY() == p.getY())
	{
		return ENPASSANT;
	}

	int dx = getLocation().getX() - p.getX();
	int dy = getLocation().getY() - p.getY();
	if (dx == _direction)
	{
		if (abs(dy) == 1 && getBoard()->pieceAt(p) != nullptr
			&& getBoard()->pieceAt(p)->getColor() != getColor())
		{
			return NORMAL;
		}
		if (dy == 0 && getBoard()->pieceAt(p) == nullptr)
		{
			return NORMAL;
		}
	}
	if ((dx == 2 * _direction)
		&& (getBoard()->pieceAt(p) == nullptr)
		&& (getBoard()->pieceAt(Point(p.getX() + _direction, p.getY())) == nullptr)
		&& (_moved == false))
	{
		return DOUBLESTEP;
	}
	return ILLEGAL;
}

void Pawn::tryToMove(Point p)
{
	MoveType move = canMove(p);
	if (move != ILLEGAL && !pin(p))
	{
		_moved = true;
		if (move == DOUBLESTEP)
		{
			getBoard()->move(getLocation(), p, Point(p.getX() + _direction, p.getY()));
		}
		else
		{
			if (move == ENPASSANT)
			{
				Point p2(p.getX() + _direction, p.getY());
				delete getBoard()->pieceAt(p2);
				getBoard()->placePieceAt(nullptr, &p2);
			}
			getBoard()->move(getLocation(), p);
		}
	}
	else
	{
		std::cout << "\33[37;41millegal move\33[0m" << std::endl;
	}
}
