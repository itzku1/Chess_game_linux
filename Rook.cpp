// Rook.cpp

#include "Rook.h"
#include "Board.h"

Rook::Rook(Point& p, Piece::Color c, Board* b) : Piece(p, c, b, ROOK)
{
	_moved = false;
}

Rook::~Rook()
{}

bool Rook::getMoved()
{
	return _moved;
}

Piece::MoveType Rook::canMove(Point p)
{
	if (Piece::canMove(p) == ILLEGAL)
	{
		return ILLEGAL;
	}

	int dx = getLocation().getX() - p.getX();
	int dy = getLocation().getY() - p.getY();

	if (dx == 0 || dy == 0)
	{	
		int i = (dx == 0) ? getLocation().getY() : getLocation().getX();
		updateIndex(i, p);
		if (dx == 0)
		{
			while (i != p.getY())
			{
				if (getBoard()->pieceAt(Point(p.getX(), i)) != nullptr)
				{
					return ILLEGAL;
				}
				updateIndex(i, p);
			}
		}
		else
		{
			while (i != p.getX())
			{
				if (getBoard()->pieceAt(Point(i, p.getY())) != nullptr)
				{
					return ILLEGAL;
				}
				updateIndex(i, p);
			}
		}
		return NORMAL;
	}
	return ILLEGAL;
}

void Rook::updateIndex(int& i, Point p)
{
	if (getLocation().getX() - p.getX() == 0)
	{
		i = (getLocation().getY() < p.getY()) ? i + 1 : i - 1;
	}
	else
	{
		i = (getLocation().getX() < p.getX()) ? i + 1 : i - 1;
	}
}

void Rook::tryToMove(Point p)
{
	if (canMove(p) != ILLEGAL && !pin(p))
	{
		_moved = true;
		getBoard()->move(getLocation(), p);
	}
	else
	{
		std::cout << "\33[37;41millegal move\33[0m" << std::endl;
	}
}
