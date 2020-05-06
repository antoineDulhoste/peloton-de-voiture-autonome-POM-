#include "peloton.h"

Peloton::Peloton(Voiture v){
  std::vector<Voiture> vec;
  vec.push_back(v);
  this->peloton = vec;
}
Peloton::Peloton(std::vector<Voiture> v){
  this->peloton = v;
}

string Peloton::getLeaderNom(){
  return leaderNom;
}
void Peloton::setLeaderNom(string nom){
  for(unsigned i=0; i<peloton.size();i++){
    if(peloton.at(i).getNom() == nom){
      leaderNom=nom;
      break;
    }
  }
  std::cout<<"Peloton::setLeaderNom(string nom) error: no corresponding name found.";
}

std::vector<Voiture> Peloton::getPeloton(){
  return peloton;
}
void Peloton::setPeloton(std::vector<Voiture> p){
  this->peloton = p;
}
