// Bishop.cpp

#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(Point p, Piece::Color c, Board* b) : Piece(p, c, b, BISHOP)
{}

Bishop::~Bishop()
{}

Piece::MoveType Bishop::canMove(Point p)
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
	else
	{
		return ILLEGAL;
	}
}

void Bishop::updateIndex(int& x, int& y, Point p)
{
	x = (getLocation().getX() < p.getX()) ? x + 1 : x - 1;
	y = (getLocation().getY() < p.getY()) ? y + 1 : y - 1;
}
