#include <iostream>
class Voiture
{
public:
	Voiture(char* s,int* pDep,int* &pAr): nom(s),pointDepart(pDep),pointArrivee(pAr){};
	char* getNom(){
		return this->nom;
	};
	int* getPointArrivee(){
		return this->pointArrivee;
	};
	int* getPointDepart(){
		return this->pointDepart;
	};
	void setNom(char* s){
		this->nom=s;
	};
	void setPointArrivee(int* pDep){
		this->pointArrivee=pDep;
	};
	void setPointDepart(int* pAr){
		this->pointDepart= pAr;
	};
	~Voiture(){
		delete pointDepart;
		delete pointArrivee;
	};
private:
	char* nom;
	int * pointDepart;
	int * pointArrivee;
};