#include <vector>

#ifndef MY_HEADER_H
#define MY_HEADER_H


class Point
{
public:
	Point(int id,int x, int y);
	int getX();
	int getY();
	int getId();
	void setX(int x);
	void setY(int y);
	void setId(int id);
	std::vector<int> getDestinations();
	void setDestination(int id);
	void rmDestination(int id);
	~Point();

private:
	int id;
	int x;
	int y;
	std::vector<int> destinations;	//id of Points
};
#endif
