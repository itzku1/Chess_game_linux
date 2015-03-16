// Point.cpp

#include "Point.h"

Point::Point() : _x(-1), _y(-1)
{}

Point::Point(int x, int y) : _x(x), _y(y)
{}

Point::~Point()
{}

int Point::getX()
{
	return this->_x;
}

int Point::getY()
{
	return this->_y;
}

void Point::setX(int x)
{
	this->_x = x;
}

void Point::setY(int y)
{
	this->_y = y;
}

void Point::setPoint(int x, int y)
{
	this->_x = x;
	this->_y = y;
}