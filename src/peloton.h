#ifndef PELOTON_H
#define PELOTON_H

#include <vector>
#include <iostream>
#include "voiture.h"

class Peloton
{
public:
  Peloton(Voiture v);
  Peloton(std::vector<Voiture>  v);

  string getLeaderNom();
  void setLeaderNom(string nom);
  std::vector<Voiture> getPeloton();
  void setPeloton(std::vector<Voiture> p);

private:
  string leaderNom;
  std::vector<Voiture> peloton;
};
#endif
