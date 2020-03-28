#include "voiture.h"

Voiture::Voiture(char* name,int pDep,int pAr): nom(name),pointDepart(pDep),pointArrivee(pAr){};

char* Voiture::getNom(){
	return this->nom;
};
int Voiture::getPointArrivee(){
	return this->pointArrivee;
};
int Voiture::getPointDepart(){
	return this->pointDepart;
};

void Voiture::setNom(char* name){
	this->nom=name;
};
void Voiture::setPointArrivee(int pDep){
	this->pointArrivee=pDep;
};
void Voiture::setPointDepart(int pAr){
	this->pointDepart= pAr;
};

Voiture::~Voiture(){
};
