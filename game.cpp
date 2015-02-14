#include "game.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>
using namespace std;
//Методы класса Figure
int Figure::NumberOfForms[7];
Point**** Figure::mas;
Figure::Figure(int a)
{
	form = a;
	position = 0;
	change(Point (5,20));
}

Point &Figure::operator [] (int i)
{
	return dot[i];
}

void Figure::rotate()
{
	position = ++position%NumberOfForms[form];
	change(dot[0]);
};

void Figure::change(Point A)
{
	for (int i = 0; i < 4; ++i)
		dot[i] = A+mas[form][position][i];
}

void Figure::move(int x, int y)
{
	Point temp(x,y);
	change(temp + &dot[0]);
}

void Figure::fullmas()
{
	NumberOfForms[0] = 2;
	NumberOfForms[1] = 1;
	NumberOfForms[2] = 4;
	NumberOfForms[3] = 2;
	NumberOfForms[4] = 2;
	NumberOfForms[5] = 4;
	NumberOfForms[6] = 4;
	mas = new Point*** [7];
	for (int i = 0; i<7; i++)
	{
		mas[i] = new Point**[NumberOfForms[i]];
		for (int k = 0;k<NumberOfForms[i];k++)
		{
			mas[i][k]= new Point* [4];
			for (int j = 0; j<4; j++)
				mas[i][k][j] = new Point;
		}
	}
				//Опеределение начального отношения точек прямой
	*mas[0][0][1]=Point (0,-1);
	*mas[0][0][2]=Point (0, 1);
	*mas[0][0][3]=Point (0, 2);
				//Определение начального отношения точек квадрата
	*mas[1][0][1]=Point (0, 1);
	*mas[1][0][2]=Point (1, 0);
	*mas[1][0][3]=Point (1, 1);
				//Определение начального отношения точек Т-образной
	*mas[2][0][1]=Point (-1, 0);
	*mas[2][0][2]=Point (0, 1);
	*mas[2][0][3]=Point (1, 0);
				//Определение начального отношения точек зигзага
	*mas[3][0][1]=Point (-1, 0);
	*mas[3][0][2]=Point (0, -1);
	*mas[3][0][3]=Point (1,-1);
				//Определение начального отношения точек обратного зигзака
	*mas[4][0][1]=Point (1,0);
	*mas[4][0][2]=Point (0,-1);
	*mas[4][0][3]=Point (-1, -1);
				//Определение начального отношения L-образной (Зеркальной)
	*mas[5][0][1]=Point (-1, 1);
	*mas[5][0][2]=Point (-1,0);
	*mas[5][0][3]=Point (1,0);
				//Определение начального отношения L-образной
	*mas[6][0][1]=Point (1,1);
	*mas[6][0][2]=Point (1,0);
	*mas[6][0][3]=Point (-1,0);
	for (int i = 0; i < 7; ++i)
		for (int k=1; k<NumberOfForms[i]; k++)
			for (int j=0;j<4;j++)
				(*mas[i][k][j])=mas[i][k-1][j]->rotate();
}

Point Figure::clearDot(int i)
{
	return *mas[form][position][i];
}
//Методы Field
Field::Field()
{
	points = 0;
	for (int i=0; i < 21; ++i)
		mas[0][i] = mas[11][i] = 1;
	for (int i=1; i < 11; ++i)
		mas[i][0] = 1;
}
bool Field::check(Figure* L)
{
	static int tempx;
	static int tempy;
	for (int i = 0; i < 4; ++i)
	{
		tempx = (*L)[i].getx();
		tempy = (*L)[i].gety();
		if (mas[tempx + 1][tempy + 1]==1)
			return false;
	}
	return true;
}
void Field::countpoints(int number, ofstream &logfile)
{
	switch (number)
	{
		case 1: points+=100; break;
		case 2:	points+=300; break;
		case 3: points+=800; break;
		case 4: points+=1500; break;
	}
	cout << "Number = " << number << "; Your points: " << points << endl;
	logfile << "Number = " << number << "; Your points: " << points << endl;
	return;
}


void Field::checkendgame(ofstream& logfile)
{
	for (int i = 1; i < 11; i++)
		if (mas[i][2]==1)
		{
			cout << "Конец игры" << endl;
			time_t temp = time(NULL);
			logfile << "Конец Игры\n" << ctime(&temp);
			ofstream Highscore("Highscore.txt", ios::app);
			Highscore << "NewPlayer " << ctime(&temp) << points << endl;
			Highscore.close();
			exit(0);
		}
}

int Field::check(int speed, ofstream& logfile)
{
	int number = 0;
	int temp;
	for (int i=1; i < 21; ++i)
	{
		temp = 1;
		for (int j = 1; j<11; ++j)
			temp *= mas[j][i];
		if (temp == 1)
		{
			for (int k = i+1; k < 21; ++k)
				for (int j = 1; j<11;j++)
					mas[j][k-1]=mas[j][k];
			--i;
			number++;
		}
	}
	if (number > 0)
	{
		countpoints(number,logfile);
		if (points<=20000)
			speed = points / 1000;
		cout << "Speed is: " << speed << endl;
	}
	return speed;
}

void Field::save(Figure* L)
{
	static int tempx;
	static int tempy;
	for (int i = 0; i < 4; ++i)
	{
		tempx = (*L)[i].getx();
		tempy = (*L)[i].gety();
		mas[tempx + 1][tempy + 1] = 1;
	}
}


int* Field::operator [] (int i)
{
	return mas[i];
}
