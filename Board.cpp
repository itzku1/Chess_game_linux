// Board.cpp

#include "Board.h"

using namespace std;

Board::Board()
{
	_turn = Piece::WHITE;
	_enPassant = Point();
	
	// Initialize new board.
	Point p(0, 0);
	placePieceAt(new Rook(p, Piece::BLACK, this), &p);
	p.setY(7);
	placePieceAt(new Rook(p, Piece::BLACK, this), &p);
	p.setY(1);
	placePieceAt(new Knight(p, Piece::BLACK, this), &p);
	p.setY(6);
	placePieceAt(new Knight(p, Piece::BLACK, this), &p);
	p.setY(2);
	placePieceAt(new Bishop(p, Piece::BLACK, this), &p);
	p.setY(5);
	placePieceAt(new Bishop(p, Piece::BLACK, this), &p);
	p.setY(3);
	placePieceAt(new Queen(p, Piece::BLACK, this), &p);
	p.setY(4);
	placePieceAt(new King(p, Piece::BLACK, this), &p);
	_kingsPos[1] = p;

	p.setX(1);
	for (int i = 0; i < WIDTH; ++i)
	{
		p.setY(i);
		placePieceAt(new Pawn(p, Piece::BLACK, this), &p);
	}

	for (int i = 2; i < WIDTH - 2; ++i)
	{
		p.setX(i);
		for (int j = 0; j < WIDTH; ++j)
		{
			p.setY(j);
			placePieceAt(nullptr, &p);
		}
	}
	
	p.setPoint(7, 0);
	placePieceAt(new Rook(p, Piece::WHITE, this), &p);
	p.setY(7);
	placePieceAt(new Rook(p, Piece::WHITE, this), &p);
	p.setY(1);
	placePieceAt(new Knight(p, Piece::WHITE, this), &p);
	p.setY(6);
	placePieceAt(new Knight(p, Piece::WHITE, this), &p);
	p.setY(2);
	placePieceAt(new Bishop(p, Piece::WHITE, this), &p);
	p.setY(5);
	placePieceAt(new Bishop(p, Piece::WHITE, this), &p);
	p.setY(3);
	placePieceAt(new Queen(p, Piece::WHITE, this), &p);
	p.setY(4);
	placePieceAt(new King(p, Piece::WHITE, this), &p);
	_kingsPos[0] = p;

	p.setX(6);
	for (int i = 0; i < WIDTH; ++i)
	{
		p.setY(i);
		placePieceAt(new Pawn(p, Piece::WHITE, this), &p);
	}
}

Board::~Board()
{}

Piece* Board::pieceAt(Point p)
{
	return _myBoard[p.getX()][p.getY()];
}

Piece* Board::pieceAt(int x, int y)
{
	return _myBoard[x][y];
}

void Board::placePieceAt(Piece* p, Point* pt)
{
	_myBoard[pt->getX()][pt->getY()] = p;
}

int Board::getTurn()
{
	return _turn;
}

void Board::setKingPos(Point p)
{
	_kingsPos[_turn] = p;
}

void Board::move()
{
	_turn = 1 - _turn;
}

void Board::move(Point p1, Point p2)
{
	move(p1, p2, Point());
}

void Board::move(Point p1, Point p2, Point enP)
{
	_enPassant.setPoint(enP.getX(), enP.getY());
	if (pieceAt(p2) != nullptr)
	{
		delete pieceAt(p2);
	}
	placePieceAt(pieceAt(p1), &p2);
	pieceAt(p2)->setLocation(p2);
	placePieceAt(nullptr, &p1);
	
	// save the new current of the king.
	if (pieceAt(p2)->getType() == Piece::KING)
	{
		_kingsPos[_turn] = p2;
	}

	// creates new queen if a pawn reached the end of the board.
	if (pieceAt(p2)->getType() == Piece::PAWN && (p2.getX() == 0 || p2.getX() == WIDTH - 1))
	{
		delete pieceAt(p2);
		Piece::Color tempColor = pieceAt(p2)->getColor();
		placePieceAt(new Queen(p2, tempColor, this), &p2);
	}
	move();
}
void Board::tryToMove(Point p1, Point p2)
{
	Piece* temp = pieceAt(p1);
	if (temp != nullptr && pieceAt(p1)->getColor() == _turn)
	{
		temp->tryToMove(p2);
	}
	else
	{
		std::cout << "\33[37;41millegal move\33[0m" << std::endl;
	}
}

Point Board::getEnPassant()
{
	return _enPassant;
}

bool Board::check()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			Piece* temp = pieceAt(Point(i, j));
			if (temp != nullptr)
			{
				if (temp->getColor() != _turn)
				{
					if (temp->check(_kingsPos[_turn]) == Piece::NORMAL)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Board::checkmate()
{
	if (!check())
	{
		return false;
	}
	for (int i = _kingsPos[_turn].getX() - 1; i < _kingsPos[_turn].getX() + 2; ++i)
	{
		for (int j = _kingsPos[_turn].getY() - 1; j < _kingsPos[_turn].getY() + 2; ++j)
		{
			if (i < WIDTH && i >= 0 && j >= 0 && j < WIDTH)
			{
				Point kingPos(_kingsPos[_turn].getX(), _kingsPos[_turn].getY());
				Point p(i, j);
				if (pieceAt(_kingsPos[_turn])->check(p) == Piece::NORMAL)
				{
					Piece* temp = pieceAt(_kingsPos[_turn]);
					Piece* temp2 = pieceAt(p);
					placePieceAt(nullptr, &_kingsPos[_turn]);
					placePieceAt(temp, &p);
					_kingsPos[_turn].setPoint(p.getX(), p.getY());
					if (!check())
					{
						placePieceAt(temp, &kingPos);
						placePieceAt(temp2, &p);
						_kingsPos[_turn].setPoint(kingPos.getX(), kingPos.getY());
						return false;
					}
					else
					{
						placePieceAt(temp, &kingPos);
						placePieceAt(temp2, &p);
						_kingsPos[_turn].setPoint(kingPos.getX(), kingPos.getY());
					}
				}
			}
		}
	}
	return true;
}

void Board::printBoard()
{
	cout << LETTERS << endl << endl;
	int k = WIDTH;
	for (int i = 0; i < WIDTH; ++i)
	{
		cout << k << " ";
		for (int j = 0; j < WIDTH; ++j)
		{
			Point p(i, j);
			if (pieceAt(p) != nullptr)
			{
				string color = pieceAt(p)->getPrint();
				switch (pieceAt(p)->getType())
				{
				case Piece::PAWN:
					if ((i + j) % 2 == 0)
					{
						cout << "\33[" << color << ";46m\u265F\33[0m";
					}
					else
					{
						cout << "\33[" << color << ";42m\u265F\33[0m";
					}
					break;
				case Piece::KNIGHT:
					if ((i + j) % 2 == 0)
					{
						cout << "\33[" << color << ";46m\u265E\33[0m";
					}
					else
					{
						cout << "\33[" << color << ";42m\u265E\33[0m";
					}
					break;
				case Piece::BISHOP:
					if ((i + j) % 2 == 0)
					{
						cout << "\33[" << color << ";46m\u265D\33[0m";
					}
					else
					{
						cout << "\33[" << color << ";42m\u265D\33[0m";
					}
					break;
				case Piece::ROOK:
					if ((i + j) % 2 == 0)
					{
						cout << "\33[" << color << ";46m\u265C\33[0m";
					}
					else
					{
						cout << "\33[" << color << ";42m\u265C\33[0m";
					}
					break;
				case Piece::QUEEN:
					if ((i + j) % 2 == 0)
					{
						cout << "\33[" << color << ";46m\u265B\33[0m";
					}
					else
					{
						cout << "\33[" << color << ";42m\u265B\33[0m";
					}
					break;
				case Piece::KING:
					if ((i + j) % 2 == 0)
					{
						cout << "\33[" << color << ";46m\u265A\33[0m";
					}
					else
					{
						cout << "\33[" << color << ";42m\u265A\33[0m";
					}
					break;
				default:
					break;
				}
			}
			else
			{
				if ((i + j) % 2 == 0)
				{
					cout << "\33[0;46m \33[0m";
				}
				else
				{
					cout << "\33[0;42m \33[0m";
				}
			}
		}
		cout << " " << k << endl;
		k--;
	}
	cout << endl << LETTERS << endl;
}

void Board::deleteBoard()
{
	for (int i = 0; i < WIDTH; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (pieceAt(Point(i, j)) != nullptr)
			{
				delete pieceAt(Point(i, j));
			}
		}
	}
}
