#ifndef MY_HEADER_H
#define MY_HEADER_H


class Point
{
public:
	Point(int x, int y);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	Point getDestination(int index);
	~Point();

private:
	int x;
	int y;
	Point* destinations;
};
#endif
