// Point.h

#ifndef POINT_H
#define POINT_H


/**
 * This class represents Point on the board. Each has X and Y values.
 * The class contains trivial get and set methods.
 */
class Point
{

public:

	/*
	 * A default constructor. Creates point at (-1,-1).
	 */
	Point();

	/**
	 * A constructor. Creates point at (x,y).
	 */
	Point(int x, int y);

	/**
	 * Destructor.
	 */
	~Point();
	
	/**
	 * gets X value.
	 * @return int
	 */
	int getX();
	
	/**
	* gets Y value.
	* @return int
	*/
	int getY();

	/**
	* sets X value.
	* @param new x value.
	*/
	void setX(int x);

	/**
	* sets Y value.
	* @param new y value.
	*/
	void setY(int y);

	/**
	* sets X,Y values.
	* @param new x,y values.
	*/
	void setPoint(int x, int y);

private:

	int _x;
	int _y;
};

#endif