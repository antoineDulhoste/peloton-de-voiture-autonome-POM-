#include "map.h"

Map::Map(Point** m,int larg,int lon): map(m),largeur(larg),longueur(lon){};

Point** Map::getMap(){
	return this->map;
};
int Map::getLargeur(){
	return this->largeur;
};
int Map::getLongueur(){
	return this->longueur;
};

void Map::setMap(Point** m){
	this->map=m;
};
void Map::setLargeur(int larg){
	this->largeur=larg;
};
void Map::setLongueur(int lon){
	this->longueur= lon;
};

Map::~Map(){
	delete map;
};
