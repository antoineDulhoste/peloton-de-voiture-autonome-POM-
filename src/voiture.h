#include "point.h"
#include <vector>
#include <string>
using namespace std;
class Voiture
{
public:
	Voiture(string s,int pDep,int pAr);
	string getNom();
	int getPointArrivee();
	int getPointDepart();
	void setNom(string s);
	void setPointArrivee(int pDep);
	void setPointDepart(int pAr);
	std::vector<int> itineraire;
	int posX;
	int posY;
	~Voiture();

private:
	string nom;
	int pointDepart;
	int pointArrivee;
};
