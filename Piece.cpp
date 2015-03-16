// Piece.cpp

#include "Piece.h"
#include "Board.h"

Piece::Piece(Point p, Color c, Board* b, Type t) : _location(p), _color(c), _board(b), _type(t)
{}

Piece::~Piece()
{}

Point Piece::getLocation()
{
	return _location;
}

Piece::Color Piece::getColor()
{
	return _color;
}

Board* Piece::getBoard()
{
	return _board;
}

Piece::Type Piece::getType()
{
	return _type;
}

std::string Piece::getPrint()
{
	if (_color == WHITE)
	{
		return WHITH_PRINT;
	}
	else
	{
		return BLACK_PRINT;
	}
}

void Piece::setLocation(Point p)
{
	_location = p;
}

Piece::MoveType Piece::canMove(Point p)
{
	if (p.getX() < WIDTH && p.getY() < WIDTH)
	{
		if (_location.getX() == p.getX() && _location.getY() == p.getY())
		{
			return ILLEGAL;
		}
		if (_board->pieceAt(p) == nullptr)
		{
			return NORMAL;	
		}
		if (_board->pieceAt(p)->getColor() != _color)
		{
			return NORMAL;
		}
	}
	return ILLEGAL;
}

bool Piece::pin(Point p)
{
	if (getType() != KING)
	{
		Piece* temp = _board->pieceAt(_location);
		Piece* temp2 = _board->pieceAt(p);
		_board->placePieceAt(nullptr, &_location);
		_board->placePieceAt(temp, &p);
		if (_board->check())
		{
			_board->placePieceAt(temp, &_location);
			_board->placePieceAt(temp2, &p);
			return true;
		}
		_board->placePieceAt(temp, &_location);
		_board->placePieceAt(temp2, &p);
		return false;
	}
	return false;
}

void Piece::tryToMove(Point p)
{
	if (canMove(p) != ILLEGAL && !pin(p))
	{
		_board->move(_location, p);
	}
	else
	{
		std::cout << "\33[37;41millegal move\33[0m" << std::endl;
	}
}

Piece::MoveType Piece::check(Point p)
{
	return canMove(p);
}

bool Piece::getMoved()
{
	return true;
}
