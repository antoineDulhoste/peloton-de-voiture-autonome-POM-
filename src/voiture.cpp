#include "voiture.h"

Voiture::Voiture(string name,int pDep,int pAr): nom(name),pointDepart(pDep),pointArrivee(pAr){};

string Voiture::getNom(){
	return this->nom;
};
int Voiture::getPointArrivee(){
	return this->pointArrivee;
};
int Voiture::getPointDepart(){
	return this->pointDepart;
};

void Voiture::setNom(string name){
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
