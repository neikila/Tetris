class Point
{
	int x;
	int y;
public:
	int getx(void);
	int gety(void);
	Point operator + (Point*);
	Point (int=0, int=0);
	Point rotate();
};
