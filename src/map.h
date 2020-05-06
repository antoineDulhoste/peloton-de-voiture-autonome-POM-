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

	std::vector<Peloton> getPelotons();
	void setPelotons(std::vector<Peloton> v);

	int getLargeur();
	int getLongueur();
	void setRoute(int index1, int index2, double vMin, double vMax);

	std::vector<int> getItineraireBetween(int indexDepart, int indexArrivee);
	Voiture * getVoitureFromPeloton(string name);
	void avancerPelotons();

	~Map();


private:
	std::vector<Point> points;
	std::vector<Voiture> voitures;
	std::vector<Peloton> pelotons;
	int nbPoints;
	int largeur;
	int longueur;
	double costForIndexToIndex(int index1, int index2);
};

#endif
