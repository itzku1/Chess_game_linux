// King.cpp

#include "King.h"
#include "Board.h"

King::King(Point& p, Piece::Color c, Board* b) : Piece(p, c, b, KING)
{
	_moved = false;
}

King::~King()
{}

Piece::MoveType King::canMove(Point p)
{
	if (Piece::canMove(p) == ILLEGAL)
	{
		return ILLEGAL;
	}

	int dx = getLocation().getX() - p.getX();
	int dy = getLocation().getY() - p.getY();

	// normal move of king.
	if ((dx == 0 && abs(dy) == 1) || (abs(dx) == 1 && dy == 0) || (abs(dx) == 1 && abs(dy) == 1))
	{
		if (getBoard()->pieceAt(p) == nullptr || getBoard()->pieceAt(p)->getColor() != getColor())
		{
			Point temPoint(getLocation().getX(), getLocation().getY());
			getBoard()->setKingPos(p);
			Piece* temp = getBoard()->pieceAt(getLocation());
			Piece* temp2 = getBoard()->pieceAt(p);
			getBoard()->placePieceAt(nullptr, &temPoint);
			getBoard()->placePieceAt(temp, &p);
			if (!getBoard()->check())
			{
				getBoard()->setKingPos(getLocation());
				getBoard()->placePieceAt(temp, &temPoint);
				getBoard()->placePieceAt(temp2, &p);
				return NORMAL;
			}
			else
			{
				getBoard()->setKingPos(getLocation());
				getBoard()->placePieceAt(temp, &temPoint);
				getBoard()->placePieceAt(temp2, &p);
				return ILLEGAL;
			}
		}
	}

	// castling.
	if (!_moved && abs(dy) == 2 && dx == 0)
	{
		int i = getLocation().getY();
		if (getBoard()->check())
		{
			return ILLEGAL;
		}
		i = (getLocation().getY() < p.getY()) ? i + 1 : i - 1;
		int counter = 0;
		while ((i > 0) && (i < WIDTH - 1))
		{
			if (getBoard()->pieceAt(Point(p.getX(), i)) != nullptr )
			{
				return ILLEGAL;
			}
			if (counter < 2)
			{
				int tempX = p.getX();
				int tempY = p.getY();
				p.setPoint(getLocation().getX(), getLocation().getY());
				Piece* temp = getBoard()->pieceAt(getLocation());
				getBoard()->placePieceAt(nullptr, &p);
				p.setPoint(getLocation().getX(), i);
				getBoard()->placePieceAt(temp, &p);
				if (getBoard()->check())
				{
					return ILLEGAL;
				}
				else
				{
					getBoard()->placePieceAt(nullptr, &p);
					p.setPoint(getLocation().getX(), getLocation().getY());
					getBoard()->placePieceAt(temp, &p);
					p.setPoint(tempX, tempY);
				}
			}
			++counter;
			i = (getLocation().getY() < p.getY()) ? i + 1 : i - 1;
		}
		if (getBoard()->pieceAt(p.getX(), i)->getType() == Piece::ROOK
				&& !(getBoard()->pieceAt(p.getX(), i)->getMoved()))
		{
			return CASTLE;
		}
	}
	return ILLEGAL;
}

void King::tryToMove(Point p)
{
	MoveType move = canMove(p);
	if (move != ILLEGAL && !pin(p))
	{
		_moved = true;
		if (move == CASTLE)
		{
			// moves the rook accordingly.
			if (p.getY() == 2)
			{
				getBoard()->move(Point(p.getX(), 0), Point(p.getX(), 3));
			}
			else
			{
				getBoard()->move(Point(p.getX(), 7), Point(p.getX(), 5));
			}
			getBoard()->move();
			getBoard()->move(getLocation(), p);
		}
		else
		{
			getBoard()->move(getLocation(), p);
		}
	}
	else
	{
		std::cout << "\33[37;41millegal move\33[0m" << std::endl;
	}
}
