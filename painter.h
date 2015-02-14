#include "game.h"
#ifndef PAINTER_H
#define PAINTER_H 
#define EXTRA 10 	//Отступ от границы окна
#define GRADE 20	//Шаг "клетки"
class Painter
{
public:
	void DrowField(void);
	void DrowFigure(Figure*);
	void DrowField(Field);
	void DrowNext(Figure*);
};
    



#endif  
