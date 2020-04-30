#include "point.h"

Point::Point(int id, int x, int y): id(id), x(x), y(y){};

int Point::getX(){return this->x;}
void Point::setX(int x){this->x=x;}
int Point::getY(){return this->y;}
void Point::setY(int y){this->y=y;}
int Point::getId(){return this->id;}
void Point::setId(int id){this->id=id;}

std::vector<destination> Point::getDestinations(){
	return destinations;
}
void Point::addDestination(int index, double cost, int vMin, int vMax){
	destination dest = {index, cost, vMin, vMax};
	destinations.push_back(dest);
}

double Point::getCostForDestIndex(int index){
	for(unsigned i=0;i<destinations.size();i++){
		if(destinations.at(i).id == index)
			return destinations.at(i).cost;
	}
	return -1;
}

Point::~Point(){};
