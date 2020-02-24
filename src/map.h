#include "point.h"
class Map
{
public:
	Map(Point** m,int larg,int lon);
	Point** getMap();
	int getLargeur();
	int getLongueur();
	void setMap(Point** m);
	void setLargeur(int larg);
	void setLongueur(int lon);
	~Map();

private:
	Point** map;
	int largeur;
	int longueur;
};
