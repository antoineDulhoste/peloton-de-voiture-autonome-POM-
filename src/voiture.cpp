#include "voiture.h"

Voiture::Voiture(char* name,Point* pDep,Point* &pAr): nom(name),pointDepart(pDep),pointArrivee(pAr){};

char* Voiture::getNom(){
	return this->nom;
};
Point* Voiture::getPointArrivee(){
	return this->pointArrivee;
};
Point* Voiture::getPointDepart(){
	return this->pointDepart;
};

void Voiture::setNom(char* name){
	this->nom=name;
};
void Voiture::setPointArrivee(Point* pDep){
	this->pointArrivee=pDep;
};
void Voiture::setPointDepart(Point* pAr){
	this->pointDepart= pAr;
};

Voiture::~Voiture(){
	delete pointDepart;
	delete pointArrivee;
};
