#include "point.h"
#include <stdlib.h>
#include <iostream>
#include <vector>

class Map
{
public:
	Map(int nbPoints, int larg, int lon);
	Map(std::vector<Point> m, int larg, int lon);

	std::vector<Point> getMap();
	void setMap(std::vector<Point> m);

	int getLargeur();
	int getLongueur();
	void setLargeur(int larg);
	void setLongueur(int lon);

	~Map();

private:
	std::vector<Point> points;
	int nbPoints;
	int largeur;
	int longueur;
};
