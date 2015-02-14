#include "point.h"
#include <fstream>
class Figure
{
private:
	Point dot[4];				//Каждая фигура характеризуется 4-мя квадратиками, каждый из которых характеризуется одной точкой.
	int position;				//Какое (условно) по счету положение занимает фигура в данный момент. От этого зависит как отсчитываются все точки относительно
						//"главной" точки.
						//form - номер фигуры, которая создается:
						//0 - линия; 1 - квадрат; 2 - Т-образная; 3 - зигзак; 4 - зигзак (зеркальный); 5 - L-образная (зеркальная); 6 - L-образная;
	static int NumberOfForms[7];
	static Point**** mas;
public:
	int form;
	Figure(int=0);
	void rotate ();				//Функция вращения по часовой.
	void change (Point);			//Функция рассчета координат 3 точек. Аргументы - координаты "главной" точки, от которой отсчитываются остальные точки.
	static void fullmas();			//Функция для автоматического расчета всего mas. Внутри необходимо задать стартовое положение.
	Point &operator[] (int);
	void move(int=0,int=0);
	Point clearDot (int);
};

class Field
{
	int points;
	int mas[12][24];
public:
	Field();
	void checkendgame(std::ofstream&);
	int check(int, std::ofstream&);
	bool check (Figure*);
	void save (Figure*);
	int* operator[](int);
	void countpoints(int, std::ofstream&);
};
