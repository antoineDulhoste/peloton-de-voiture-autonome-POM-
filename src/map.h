#include "point.h"
#include "voiture.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <algorithm>

#ifndef MAP_H
#define MAP_H

class Map
{
public:
	Map(std::vector<Point> m, int larg, int lon);

	std::vector<Point> getPoints();
	void setPoints(std::vector<Point> m);

	std::vector<Voiture> getVoitures();
	void setVoitures(std::vector<Voiture> v);

	int getLargeur();
	int getLongueur();
	void setRoute(int index1, int index2, int vMin, int vMax);

	int getPointPos(int index, char xORy);
	std::vector<int> getItineraireBetween(int indexDepart, int indexArrivee);

	void avancerVoitures();

	~Map();

private:
	std::vector<Point> points;
	std::vector<Voiture> voitures;
	int nbPoints;
	int largeur;
	int longueur;
	double costForIndexToIndex(int index1, int index2);
};

#endif
