#include "point.h"

Point::Point(bool drive,char* img): image(img),drivable(drive){};

char* Point::getImage(){
	return this->image;
};

void Point::setImage(char* img){
	this->image=img;
};

bool Point::getDrivable(){
	return this->drivable;
};

void Point::setDrivable(bool drive){
	this->drivable=drive;
};

Point::~Point(){
	delete image;
};
