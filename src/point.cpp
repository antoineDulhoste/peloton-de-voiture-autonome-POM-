#include "point.h"

Point::Point(int x, int y): x(x), y(y){};

int Point::getX(){return this->x;}
void Point::setX(int x){this->x=x;}
int Point::getY(){return this->y;}
void Point::setY(int y){this->y=y;}

Point Point::getDestination(int index){
	return destinations[index];
}

Point::~Point(){};
