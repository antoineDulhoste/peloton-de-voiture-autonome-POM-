#include "map.h"

Map::Map(int nbPoints, int larg, int lon):nbPoints(nbPoints), largeur(larg),longueur(lon){
	for(int i = 0; i<nbPoints; i++){
		int x= rand()%lon;
		int y= rand()%larg;
		points.push_back(Point(x,y));
		std::cout<<"point x:"<<x<<" y:"<<y<<std::endl;
	}
}

Map::Map(std::vector<Point> m,int larg,int lon): points(m),largeur(larg),longueur(lon){
	nbPoints = m.size();
}

std::vector<Point> Map::getMap(){
	return this->points;
}
void Map::setMap(std::vector<Point> m){
	this->points=m;
}

int Map::getLargeur(){return this->largeur;}
int Map::getLongueur(){return this->longueur;}
void Map::setLargeur(int larg){this->largeur=larg;}
void Map::setLongueur(int lon){this->longueur= lon;}

Map::~Map(){}
