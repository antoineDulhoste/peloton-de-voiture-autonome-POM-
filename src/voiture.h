#include "point.h"
#include <stack>
using namespace std;
class Voiture
{
public:
	Voiture(char* s,int pDep,int pAr);
	char* getNom();
	int getPointArrivee();
	int getPointDepart();
	void setNom(char* s);
	void setPointArrivee(int pDep);
	void setPointDepart(int pAr);
	stack<int> itineraire;
	~Voiture();

private:
	char* nom;
	int pointDepart;
	int pointArrivee;
};
