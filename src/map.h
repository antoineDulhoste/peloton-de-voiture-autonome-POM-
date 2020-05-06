#ifndef MAP_H
#define MAP_H

#include "point.h"
#include "peloton.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <algorithm>

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
	void setRoute(int index1, int index2, double vMin, double vMax);

	std::vector<int> getItineraireBetween(int indexDepart, int indexArrivee);

	void avancerVoitures();


	~Map();

	std::vector<Peloton> pelotons;
private:
	std::vector<Point> points;
	std::vector<Voiture> voitures;
	int nbPoints;
	int largeur;
	int longueur;
	double costForIndexToIndex(int index1, int index2);
};

#endif
