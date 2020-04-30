#include "point.h"
#include <vector>
#include <string>
using namespace std;
class Voiture
{
public:
	Voiture(string s,int pDep,int pAr);
	string getNom();
	double getVitesse();
	int getPointArrivee();
	int getPointDepart();
	void setNom(string s);
	void setVitesse(double v);
	void setPointArrivee(int pDep);
	void setPointDepart(int pAr);
	std::vector<int> itineraire;
	double posX;
	double posY;
	~Voiture();

private:
	string nom;
	double vitesse;
	int pointDepart;
	int pointArrivee;
};
