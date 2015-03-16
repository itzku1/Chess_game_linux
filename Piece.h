// Piece.h

#ifndef PIECE_H_
#define PIECE_H_

#include "Point.h"
#include <string>

// codes of printing black or white piece.
const std::string WHITH_PRINT = "37";
const std::string BLACK_PRINT = "30";

class Board;

/**
 * This class is a base class of all types of pieces in a chess game.
 * Each piece has a Color (black or white), a type of its own and can make different moves
 * according to the type of the piece; point which is the current location of the piece, and
 * pointer to the board. This class responsible to the general actions that are common to all
 * of the pieces.
 */
class Piece
{

public:

	// Color of a piece.
	enum Color : int
	{
		WHITE = 0,
		BLACK = 1
	};

	/**
	 * All types of possible moves: 
	 * NORMAL - for a normal, legal move or ILLEGAL if not.
	 * CASTLE - for king and rook.
	 * DOUBLESTEP and ENPASSANT - for pawns.
	 */
	enum MoveType : int
	{
		ILLEGAL,
		NORMAL,
		CASTLE,
		DOUBLESTEP,
		ENPASSANT
	};

	// Pieces types.
	enum Type : int
	{
		PIECE,
		PAWN,
		KNIGHT,
		BISHOP,
		ROOK,
		QUEEN,
		KING
	};

	/**
	 * A constructor.
	 * Creates new piece object as told in the class description.
	 * Initializing the location, color and type of a piece and the pointer to the board.
	 * @param p - Point for the current location on the board.
	 * @param c - Color of the piece.
	 * @param b - pointer to the Board.
	 * @param t - type of the piece.
	 */
	Piece(Point p, Color c, Board* b, Type t);

	/**
	 * Destructor.
	 */
	virtual ~Piece();

	/**
	 * Returns the current location of a piece.
	 * @return Point.
	 */
	Point getLocation();

	/**
	 * Returns the color of a piece.
	 * @return Color.
	 */
	Color getColor();

	/**
	 * Returns the board.
	 * @return Board.
	 */
	Board* getBoard();

	/**
	 * Sets new location of a piece.
	 * @param Point.
	 */
	void setLocation(Point p);

	/**
	 * Checks if a piece can move to a given point.
	 * @param Point.
	 * @return the type of the move that can be done, ILLEGAL if move to this point is not legal.
	 */
	MoveType check(Point p);

	/**
	 * Checks if a piece is pinned to the current location.
	 * A piece is pinned if move of it will expose the king to threat.
	 * @param Point.
	 * @return boolean true if the piece cannot move or false otherwise.
	 */
	bool pin(Point p);

	/**
	 * This method after all the checks were made sends to the board the next move to do.
	 * @param Point.
	 */
	virtual void tryToMove(Point p);

	/**
	 * This method is for the rook to get data to the king in a CASTLE move.
	 * @param Point.
	 * @return true if the rook already moved else false.
	 */
	virtual bool getMoved();

	/**
	 * Returns the type of a piece.
	 * @return Type.
	 */
	virtual Type getType();

	/**
	 * Returns the color code of a piece to print.
	 * @return string.
	 */
	std::string getPrint();

protected:

	/**
	 * This method is responsible to check if a piece can move to the given point.
	 * As a piece the checks to be done for each moving piece are: check if a move is inside
	 * the board, if a move isn't taking you to current location, if you're not move to your
	 * own piece location.
	 * From here, each piece can overload this function as a protected one and set it's own
	 * way to move and check for legality.
	 * @param Point.
	 * @return the kind of the move.
	 */
	virtual MoveType canMove(Point p);

private:

	Point _location;

	Color _color;

	Board* _board;

	Type _type;

};


#endif
