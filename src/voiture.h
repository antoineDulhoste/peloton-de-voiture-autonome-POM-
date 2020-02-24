#include "point.h"
#include <queue>
using namespace std;
class Voiture
{
public:
	Voiture(char* s,Point* pDep,Point* &pAr);
	char* getNom();
	Point* getPointArrivee();
	Point* getPointDepart();
	void setNom(char* s);
	void setPointArrivee(Point* pDep);
	void setPointDepart(Point* pAr);
	queue<Point*> itineraire;
	~Voiture();

private:
	char* nom;
	Point* pointDepart;
	Point* pointArrivee;
};
