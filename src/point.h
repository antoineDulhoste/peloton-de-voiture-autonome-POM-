#include <vector>
#include <iostream>

#ifndef POINT_H
#define POINT_H

struct destination{
	int id;
	double cost;
	double vMin;
	double vMax;
};

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
	std::vector<destination> getDestinations();
	void addDestination(int index, double cost, double vMin, double vMax);
	void addCostForDest(double cost);
	double getCostForDestIndex(int index);
	double getVMinForDestIndex(int index);
	double getVMaxForDestIndex(int index);
	~Point();

private:
	int id;
	int x;
	int y;
	std::vector<destination> destinations;
};
#endif
