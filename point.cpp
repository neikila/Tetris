#include "point.h"
//Класс Point
int Point::getx(void)
{
	return x;
}

int Point::gety(void)
{
	return y;
}

Point::Point (int a, int b)
{
	x=a;
	y=b;
}

Point Point::operator + (Point* A)
{
	Point temp(x+A->x,y+A->y);
	return temp;
}


Point Point::rotate()
{
	Point temp(y,-x);
	return temp;
}
