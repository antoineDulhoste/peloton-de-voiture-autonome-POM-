#include "voiture.h"

Voiture::Voiture(string name,int pDep,int pAr): nom(name),pointDepart(pDep),pointArrivee(pAr){
	this->vitesse = 0;
};

string Voiture::getNom(){
	return this->nom;
};
double Voiture::getVitesse(){
	return this->vitesse;
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
void Voiture::setVitesse(double v){
	this->vitesse =v;
};
void Voiture::setPointArrivee(int pDep){
	this->pointArrivee=pDep;
};
void Voiture::setPointDepart(int pAr){
	this->pointDepart= pAr;
};

Voiture::~Voiture(){
};
