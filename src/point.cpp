#include "point.h"

Point::Point(int id, int x, int y): id(id), x(x), y(y){};

int Point::getX(){return this->x;}
void Point::setX(int x){this->x=x;}
int Point::getY(){return this->y;}
void Point::setY(int y){this->y=y;}
int Point::getId(){return this->id;}
void Point::setId(int id){this->id=id;}

std::vector<int> Point::getDestinations(){
	return destinations;
}
void Point::setDestination(int id){
	destinations.push_back(id);
}
void Point::rmDestination(int id){
}

Point::~Point(){};
