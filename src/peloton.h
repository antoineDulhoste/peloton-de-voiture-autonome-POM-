#ifndef PELOTON_H
#define PELOTON_H

#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Peloton
{
public:
  Peloton(string idLead);
  Peloton(string idLead, std::vector<string> peloton);

  string getLeader();
  void setLeader(string v);
  std::vector<string> getPeloton();
  void setPeloton(std::vector<string> p);

  bool getVisible();
  void setVisible(bool vis);

  void addElement(string v);
  void removeElement(string v);

private:
  string leader;
  std::vector<string> peloton;
  bool visible = true;
};

#endif
