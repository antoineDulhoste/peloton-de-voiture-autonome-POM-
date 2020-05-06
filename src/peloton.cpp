#include "peloton.h"

Peloton::Peloton(string idLead): leader(idLead){
  peloton.push_back(idLead);
}
Peloton::Peloton(string lead, std::vector<string> peloton): leader(lead), peloton(peloton){}


string Peloton::getLeader(){
  return leader;
}
void Peloton::setLeader(string v){
  for(unsigned i=0; i<peloton.size();i++){
    if(peloton.at(i) == v){
      leader=v;
      break;
    }
  }
  std::cout<<"Peloton::setLeader(string v) error: no corresponding voiture found. Make sure you didnt misspell name";
}

std::vector<string> Peloton::getPeloton(){
  return peloton;
}
void Peloton::setPeloton(std::vector<string> p){
  this->peloton = p;
}

void Peloton::addElement(string v){
  peloton.push_back(v);
}

void Peloton::removeElement(string v){
  for(unsigned i=0; i<peloton.size();i++){
    if(peloton.at(i)== v){
      peloton.erase(peloton.begin()+i);
      return;
    }
  }
}
