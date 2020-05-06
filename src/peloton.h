#ifndef PELOTON_H
#define PELOTON_H

#include "voiture.h"
#include <vector>
#include <iostream>

class Peloton
{
public:
  Peloton(string idLead);
  Peloton(string idLead, std::vector<string> peloton);

  string getLeader();
  void setLeader(string v);
  std::vector<string> getPeloton();
  void setPeloton(std::vector<string> p);

  void addElement(string v);
  void removeElement(string v);

private:
  string leader;
  std::vector<string> peloton;
};

#endif
