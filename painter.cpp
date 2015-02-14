#include "painter.h"
#include <GL/glut.h>
enum {M_HI=500,M_WI=200};

void Painter::DrowField(void)
{
	glColor3f(1.0,1.0,1.0);
	glLineWidth(1);
	glBegin(GL_LINES);
		for (int i = 0; i <=M_WI/GRADE; i++) 
		{
			glVertex2f(i*GRADE + EXTRA,0.0);
			glVertex2f(i*GRADE + EXTRA,500.0);
		} 

		for (int i = 0; i < M_HI/GRADE; i++) 
		{
			glVertex2f(EXTRA,GRADE*i + EXTRA);
			glVertex2f(M_WI + EXTRA,GRADE*i + EXTRA);
		}
	glEnd();

	glColor3f(0.0,1.0,0.0);
	int width = 20;
	glRecti(M_WI + EXTRA,EXTRA,M_WI + EXTRA + width, 500 - EXTRA);

	glRecti(M_WI + EXTRA + width + 50,M_HI - 140 - 50,M_WI + EXTRA + width + 50 + 140,M_HI - 130 - 50);
	glRecti(M_WI + EXTRA + width + 50,M_HI - 50,M_WI + EXTRA + width + 60,M_HI - 140 - 50);
	glRecti(M_WI + EXTRA + width + 50,M_HI - 50,M_WI + EXTRA + width + 50 + 140,M_HI  - 10 - 50);
	glRecti(M_WI + EXTRA + width + 50 + 140,M_HI - 50,M_WI + EXTRA + width + 50 + 130,M_HI - 140 - 50);
	glColor3f(1.0,1.0,1.0);
	glRecti(0,0,EXTRA ,500);
	glRecti(0,500 - EXTRA,500,500);
	glRecti(0,0,500,EXTRA);
	glRecti(500 - EXTRA,0,500,500);
}

void Painter::DrowNext(Figure* L)
{
	static int deltax = M_WI + EXTRA + 20 + 130 - 2*GRADE;
	static int deltay = M_HI - 70 - 50 - GRADE;
	for (int j = 0; j < 4; j++)
	{
		int tempx = EXTRA + GRADE* L->clearDot(j).getx();
		int tempy = EXTRA + GRADE* L->clearDot(j).gety();
		glRecti(deltax + tempx,deltay+tempy,deltax + tempx+GRADE,deltay+tempy+GRADE);
	}
}

void Painter::DrowFigure(Figure *L)
{
	for (int j = 0; j < 4; j++)
	{
		int tempx = EXTRA + GRADE* (*L)[j].getx();
		int tempy = EXTRA + GRADE* (*L)[j].gety();
		glRecti(tempx,tempy,tempx+GRADE,tempy+GRADE);
	}
}

void Painter::DrowField(Field F)
{
	for (int i = 1; i < 11; i++)
		for (int j = 1; j < 21; j++)
		{
			if (F[i][j]==1)
			{
				int tempx = EXTRA + GRADE*(i-1);
				int tempy = EXTRA + GRADE*(j-1);
				glRecti(tempx,tempy,tempx+GRADE,tempy+GRADE);
			}
		}
}
