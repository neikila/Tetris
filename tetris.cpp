#include<GL/glut.h>
#include "painter.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>
using namespace std;
Figure *l;
Figure *next;
int stop = 1;
Field F;
static ofstream logfile;
int speed = 0;

void rotate()
{
	Figure temp = (*l);
	temp.rotate();
	if (F.check(&temp))
		l->rotate();
}

void move(int x)
{
	Figure temp = (*l);
	temp.move(x,0);
	if (F.check(&temp))
		l->move(x,0);
}

void movedown()
{
	Figure temp = (*l);
	temp.move(0,-1);
	if(F.check(&temp))
		l->move(0,-1);
	else
	{
		F.save(l);
		speed = F.check(speed, logfile);
		F.checkendgame(logfile);
		stop = 1;
	}
}


void display(void)
{
	static bool flag0 = false;
	glClear(GL_COLOR_BUFFER_BIT);
	Painter C;
    C.DrowField();
	C.DrowField(F);
	if (stop!=1)
		C.DrowFigure(l);
	if (next!=NULL)
		C.DrowNext(next);
	glutSwapBuffers();
}

void keyboard(int  key,int x,int y)
{
	if (stop != 1)
	{
		switch(key)
		{       
			case GLUT_KEY_LEFT: { move(-1); break; }
			case GLUT_KEY_RIGHT: { move(+1); break; }
			case GLUT_KEY_UP: { rotate(); break; }
			case GLUT_KEY_DOWN: { movedown();break; }
			case GLUT_KEY_INSERT: {exit(0);break;}
		}
		glutPostRedisplay();
	}
}

void timer(int =0)
{
	if (stop == 1)
	{
		if (next!=NULL)
		{
			*l = *next;
			delete next;
			next = new Figure(rand()%7);
		}
		else
		{
			next = new Figure(rand()%7);
			timer();
			return;
		}
		stop = 0;
	}
	movedown();
	display();
	glutTimerFunc(400 - 10*speed,timer,0);
}

int main(int argc,char**argv)
{
	srand(time(NULL));
	Figure::fullmas();
	l = new Figure;
	time_t temp;
	time(&temp);
	logfile.open("Lastgame.txt");
	logfile << "Newgame. Date: " << ctime(&temp) << endl;
	logfile << "Your score: 0\n";

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Tetris");
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,500.0,0.0,500.0,1.0,-1.0);
	glutTimerFunc(200,timer,0);
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	glutMainLoop();
    return 0;
}



