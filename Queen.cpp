// Queen.cpp

#include "Queen.h"
#include "Board.h"

Queen::Queen(Point& p, Piece::Color c, Board* b) : Piece(p, c, b, QUEEN)
{}

Queen::~Queen()
{}

Piece::MoveType Queen::canMove(Point p)
{
	if (Piece::canMove(p) == ILLEGAL)
	{
		return ILLEGAL;
	}

	int dx = getLocation().getX() - p.getX();
	int dy = getLocation().getY() - p.getY();

	if (abs(dx) == abs(dy))
	{

		int i = getLocation().getX();
		int j = getLocation().getY();
		updateIndex(i, j, p);

		while (i != p.getX())
		{
			if (getBoard()->pieceAt(Point(i, j)) != nullptr)
			{
				return ILLEGAL;
			}
			updateIndex(i, j, p);
		}
		return NORMAL;
	}
	else if (dx == 0 || dy == 0)
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

void Queen::updateIndex(int& x, int& y, Point p)
{
	x = (getLocation().getX() < p.getX()) ? x + 1 : x - 1;
	y = (getLocation().getY() < p.getY()) ? y + 1 : y - 1;
}

void Queen::updateIndex(int& i, Point p)
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
