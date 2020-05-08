#include "map.h"


Map::Map(std::vector<Point> m, int larg,int lon): points(m), largeur(larg),longueur(lon){
	nbPoints = m.size();
}

std::vector<Point> Map::getPoints(){
	return this->points;
}
void Map::setPoints(std::vector<Point> m){
	this->points=m;
}

std::vector<Voiture> Map::getVoitures(){
	return this->voitures;
}
void Map::setVoitures(std::vector<Voiture> v){
	this->voitures = v;
	for(unsigned i =0; i<voitures.size();i++){
		voitures.at(i).posX = points.at(voitures.at(i).getPointDepart()).getX();
		voitures.at(i).posY = points.at(voitures.at(i).getPointDepart()).getY();
		voitures.at(i).itineraire = getItineraireBetween(voitures.at(i).getPointDepart(), voitures.at(i).getPointArrivee());
		voitures.at(i).setVitesse((points.at(voitures.at(i).itineraire.at(0)).getVMinForDestIndex(voitures.at(i).itineraire.at(1)) +
												 			 points.at(voitures.at(i).itineraire.at(0)).getVMaxForDestIndex(voitures.at(i).itineraire.at(1))) /2); //se met a la vitesse moyenne
		std::vector<string> p;
		p.push_back(voitures.at(i).getNom());
		pelotons.push_back(Peloton(p.at(0), p));
	}
}
void Map::addVoiture(string name, int ptDepart, int ptArrive){
	voitures.push_back(Voiture(name, ptDepart, ptArrive));
	voitures.at(voitures.size()-1).posX = points.at(ptDepart).getX();
	voitures.at(voitures.size()-1).posY = points.at(ptDepart).getY();
	voitures.at(voitures.size()-1).itineraire = getItineraireBetween(ptDepart, ptArrive);
	voitures.at(voitures.size()-1).setVitesse((points.at(voitures.at(voitures.size()-1).itineraire.at(0)).getVMinForDestIndex(voitures.at(voitures.size()-1).itineraire.at(1)) +
														 points.at(voitures.at(voitures.size()-1).itineraire.at(0)).getVMaxForDestIndex(voitures.at(voitures.size()-1).itineraire.at(1))) /2);
	std::vector<string> p;
	p.push_back(voitures.at(voitures.size()-1).getNom());
	pelotons.push_back(Peloton(p.at(0), p));
}

std::vector<Peloton> Map::getPelotons(){
	return this->pelotons;
}
void Map::setPelotons(std::vector<Peloton> p){
	this->pelotons=p;
}

Voiture * Map::getVoitureFromPeloton(string name){
	for(unsigned i=0;i<voitures.size();i++){
		if(voitures.at(i).getNom() == name)
			return &voitures.data()[i];
	}
	std::cout<<"Peloton::getVoitureFromPeloton(string name) error: no corresponding voiture found. Make sure you didnt misspell name";
	return nullptr;
}

int Map::getLargeur(){return this->largeur;}
int Map::getLongueur(){return this->longueur;}

void Map::setRoute(int index1, int index2, double vMin, double vMax){
	double cost = costForIndexToIndex(index1, index2);
	points.at(index1).addDestination(index2, cost, vMin, vMax);
	points.at(index2).addDestination(index1, cost, vMin, vMax);
}

void Map::avancerPelotons(){
	double difX, difY, newX, newY;
	for(unsigned i=0; i<pelotons.size(); i++ ){
		Voiture * currentLeader = getVoitureFromPeloton(pelotons.at(i).getLeader());
		//avancer le long de leur axe d'après les positions du leader
		difX = points.at(currentLeader->itineraire.at(1)).getX() - points.at(currentLeader->itineraire.at(0)).getX();
		difY = points.at(currentLeader->itineraire.at(1)).getY() - points.at(currentLeader->itineraire.at(0)).getY();
		newX = difX * currentLeader->getVitesse() / sqrt(pow(difX,2)+pow(difY,2));
		newY = difY * currentLeader->getVitesse() / sqrt(pow(difX,2)+pow(difY,2));
		//verifier si le point a été atteint ou dépassé par le peloton
		if(((currentLeader->posX < points.at(currentLeader->itineraire.at(1)).getX() && points.at(currentLeader->itineraire.at(1)).getX() <= currentLeader->posX+newX)
		||(currentLeader->posX > points.at(currentLeader->itineraire.at(1)).getX() && points.at(currentLeader->itineraire.at(1)).getX() >= currentLeader->posX+newX))
		||((currentLeader->posY < points.at(currentLeader->itineraire.at(1)).getY() && points.at(currentLeader->itineraire.at(1)).getY() <= currentLeader->posY+newY)
		||(currentLeader->posY > points.at(currentLeader->itineraire.at(1)).getY() && points.at(currentLeader->itineraire.at(1)).getY() >= currentLeader->posY+newY))){
			//passer a la prochaine destination de l'itinéraire
			for(unsigned j=0; j<pelotons.at(i).getPeloton().size(); j++){
				Voiture * currentV = getVoitureFromPeloton(pelotons.at(i).getPeloton().at(j));
				if(currentV->itineraire.size()>2){	//si il reste au moins 2 ID dans la liste, il y a encore des points parcourir
					currentV->posX = points.at(currentV->itineraire.at(1)).getX();	//ajustement des décalages du aux arrondis
					currentV->posY = points.at(currentV->itineraire.at(1)).getY();	//ajustement des décalages du aux arrondis
					currentV->itineraire.erase(currentV->itineraire.begin());				//retirer le point passé
					bool trouverPeloton = false;
					for(unsigned k=0;k<pelotons.size();k++){	//verifier la liste des pelotons disponible et s'ajouter si possible
						if(pelotons.at(k).getVisible() && currentV->itineraire.at(0) == getVoitureFromPeloton(pelotons.at(k).getLeader())->itineraire.at(0)
						&& currentV->itineraire.at(1) == getVoitureFromPeloton(pelotons.at(k).getLeader())->itineraire.at(1)){
							trouverPeloton = true;
							pelotons.at(k).addElement(currentV->getNom());	//ajouter la voiture au peloton
							currentV->setVitesse(currentLeader->getVitesse()); //se mettre a la vitesse du leader
						}
					}
					if(!trouverPeloton){ //si pas de peloton trouve creer nouveau peloton
						std::vector<string> newPeloton;
						newPeloton.push_back(currentV->getNom());
						pelotons.push_back(Peloton(newPeloton.at(0), newPeloton));
						currentV->setVitesse((points.at(currentV->itineraire.at(0)).getVMinForDestIndex(currentV->itineraire.at(1)) +
						points.at(currentV->itineraire.at(0)).getVMaxForDestIndex(currentV->itineraire.at(1))) /2); //se met a la vitesse moyenne
					}
				}
				else{
					int ptArriv = currentV->getPointArrivee();
					int ptDepart= currentV->getPointDepart();
					string nom = currentV->getNom();
					for(unsigned k=0;k<voitures.size();k++){
						if(voitures.at(k).getNom() == currentV->getNom())
							voitures.erase(voitures.begin()+k);			//retirer de la liste des voitures car destination atteinte
					}
					addVoiture(nom, ptArriv, ptDepart); //ajout d'une nouvelle voiture faisant le chemin inverse*/
				}
			}
			pelotons.erase(pelotons.begin() + i);
			i--; //Compenser le saut d'indice du au erase
		}
		else{	//sinon continuer a avancer
			if(pelotons.at(i).getVisible()) {	//depart du peloton, mise a niveau de la vitesse pour rejoindre un autre peloton
				pelotons.at(i).setVisible(false);
				std::vector<int> pelotonList;
				unsigned prioPeloton = i;	//best current peloton is self
				Voiture * test;
				Voiture * best;
				for(unsigned k=0;k<pelotons.size();k++){	//estce que il a des pelotons qui ont la meme prochaine route que mon peloton ?
					if(!memePeloton(pelotons.at(i).getLeader(), pelotons.at(k).getLeader()) &&
					getVoitureFromPeloton(pelotons.at(i).getLeader())->itineraire.size() >2 && getVoitureFromPeloton(pelotons.at(k).getLeader())->itineraire.size() >2 &&
					getVoitureFromPeloton(pelotons.at(i).getLeader())->itineraire.at(1) == getVoitureFromPeloton(pelotons.at(k).getLeader())->itineraire.at(1) &&
					getVoitureFromPeloton(pelotons.at(i).getLeader())->itineraire.at(2) == getVoitureFromPeloton(pelotons.at(k).getLeader())->itineraire.at(2)){
						pelotonList.push_back(k);
						if(pelotons.at(k).getPeloton().size() > pelotons.at(prioPeloton).getPeloton().size()) //test de taille des pelotons
								prioPeloton = k;
						test = getVoitureFromPeloton(pelotons.at(k).getLeader());
						best = getVoitureFromPeloton(pelotons.at(prioPeloton).getLeader());
						double distanceRestanteBest = sqrt(pow(points.at(best->itineraire.at(1)).getX() - best->posX, 2)+
																					pow(points.at(best->itineraire.at(1)).getY() - best->posY,2));
						double distanceRestanteTest= sqrt(pow(points.at(test->itineraire.at(1)).getX() - test->posX, 2)+
																					pow(points.at(test->itineraire.at(1)).getY() - test->posY,2));
						if(pelotons.at(k).getPeloton().size() == pelotons.at(prioPeloton).getPeloton().size() && distanceRestanteBest > distanceRestanteTest){ //test de distance a parcourir
							prioPeloton = k;
						}
					}
				}
				//calculer la nouvelle vitesse
				if(pelotonList.size() > 0){	//si il y a des pelotons a coupler
					double newVitesse =0;
					if(prioPeloton == i){	//si je suis le meilleur peloton
						std::cout << currentLeader->getNom() << " amene les autres pelotons" << '\n';
						double distanceRestanteSelf = sqrt(pow(points.at(currentLeader->itineraire.at(1)).getX() - currentLeader->posX, 2)+
																					 pow(points.at(currentLeader->itineraire.at(1)).getY() - currentLeader->posY,2));
						int tickRestantSelf = distanceRestanteSelf/currentLeader->getVitesse() +1; //round
						for(unsigned l=0; l < pelotonList.size();l++){
							Voiture * objectif = getVoitureFromPeloton(pelotons.at(pelotonList.at(l)).getLeader());
							double distanceRestanteObj= sqrt(pow(points.at(objectif->itineraire.at(1)).getX() - objectif->posX, 2)+
																						 pow(points.at(objectif->itineraire.at(1)).getY() - objectif->posY,2));
							for(unsigned m=0; m < pelotons.at(pelotonList.at(l)).getPeloton().size(); m++){
									if((unsigned)pelotonList.at(l) <= i)
										newVitesse = distanceRestanteObj/(tickRestantSelf -1);
									else
										newVitesse = distanceRestanteObj/(tickRestantSelf -2);
									getVoitureFromPeloton(pelotons.at(pelotonList.at(l)).getPeloton().at(m))->setVitesse(newVitesse);
							}
							std::cout << "peloton a fait acceler: " <<  getVoitureFromPeloton(pelotons.at(pelotonList.at(l)).getLeader())->getNom()<<" nouvelle vitesse :" <<newVitesse<< '\n';
						}
					}
					else{		//si je dois me fixer sur un autre peloton
						//calculer la distance restante du peloton vise a parcourir
						Voiture * objectif = getVoitureFromPeloton(pelotons.at(prioPeloton).getLeader());
						double distanceRestanteObj = sqrt(pow(points.at(objectif->itineraire.at(1)).getX() - objectif->posX, 2)+
																					 pow(points.at(objectif->itineraire.at(1)).getY() - objectif->posY,2));
						int tickRestantObj = distanceRestanteObj/objectif->getVitesse()+2; //round
						double distanceRestanteSelf= sqrt(pow(points.at(currentLeader->itineraire.at(1)).getX() - currentLeader->posX, 2)+
																					 pow(points.at(currentLeader->itineraire.at(1)).getY() - currentLeader->posY,2));
						newVitesse = distanceRestanteSelf/tickRestantObj;
						std::cout << getVoitureFromPeloton(pelotons.at(i).getLeader())->getNom() << " accelere pour rejoindre le peloton de " << getVoitureFromPeloton(pelotons.at(prioPeloton).getLeader())->getNom() << "("<< newVitesse << ")"<< '\n';
						for(unsigned l=0; l < pelotons.at(i).getPeloton().size(); l++)
							getVoitureFromPeloton(pelotons.at(i).getPeloton().at(l))->setVitesse(newVitesse);
						difX = points.at(currentLeader->itineraire.at(1)).getX() - points.at(currentLeader->itineraire.at(0)).getX();
						difY = points.at(currentLeader->itineraire.at(1)).getY() - points.at(currentLeader->itineraire.at(0)).getY();
						newX = difX * currentLeader->getVitesse() / sqrt(pow(difX,2)+pow(difY,2));
						newY = difY * currentLeader->getVitesse() / sqrt(pow(difX,2)+pow(difY,2));
					}
				}
			}
			for(unsigned j=0; j<pelotons.at(i).getPeloton().size(); j++){
				Voiture * currentV = getVoitureFromPeloton(pelotons.at(i).getPeloton().at(j));
				currentV->posX += newX;
				currentV->posY += newY;
			}
		}
	}
}

bool Map::memePeloton(string n1, string n2){
	for(unsigned i=0;i<pelotons.size();i++){
		for(unsigned j=0; j<pelotons.at(i).getPeloton().size(); j++){
			if(pelotons.at(i).getPeloton().at(j) == n1){
				for(unsigned k=0; k<pelotons.at(i).getPeloton().size(); k++){
					if(pelotons.at(i).getPeloton().at(k) == n2)
						return true;
				}
				return false;
			}
		}
	}
	return false; //warning in compilation
}


double Map::costForIndexToIndex(int index1, int index2){
	return sqrt(pow(points.at(index1).getX()-points.at(index2).getX(),2)+
							pow(points.at(index1).getY()-points.at(index2).getY(),2));
}
struct destinationitineraire{
	int id;
	double cost;
	int parent;
};
struct destinationComparator{
    bool operator()(const destinationitineraire& l, const destinationitineraire& r)
    {return l.cost > r.cost;}
};
std::vector<int> Map::getItineraireBetween(int indexDepart, int indexArrivee){
	std::priority_queue<destinationitineraire, std::vector<destinationitineraire>, destinationComparator> toCheck;
	std::vector<destinationitineraire> final;
	std::vector<int> itineraire;
	double* distance= new double[points.size()];
  bool* alreadyListed= new bool[points.size()];
  for (unsigned i=0;i<points.size();i++){
    distance[i]=-1;
    alreadyListed[i]=false;
  }

  destinationitineraire index= destinationitineraire{indexDepart,0,-1};
  distance[index.id]=0;
	alreadyListed[index.id]=true;
	toCheck.push(index);
	while(!toCheck.empty()){
		index = toCheck.top();
		toCheck.pop();
		if(index.id == indexArrivee){
			itineraire.push_back(index.id);
			final.push_back(index);
			for(unsigned i=0;i<final.size();i++){
				if(final.at(final.size()-1-i).id == itineraire.at(itineraire.size()-1) && final.at(final.size()-1-i).parent != -1)
					itineraire.push_back(final.at(final.size()-1-i).parent);
			}
			std::reverse(itineraire.begin(), itineraire.end());
			return itineraire;
		}
	  for(unsigned i=0;i<points.at(index.id).getDestinations().size();i++){	//ajouter les voisins
			int voisinId = points.at(index.id).getDestinations().at(i).id;
			double voisinCost = points.at(index.id).getDestinations().at(i).cost;
	    if(!alreadyListed[voisinId] && (distance[index.id]+ voisinCost < distance[voisinId] || distance[voisinId]==-1)){
	      distance[voisinId]=distance[index.id] + voisinCost;
				toCheck.push(destinationitineraire{voisinId, distance[voisinId], index.id});
	    }
	  }
		alreadyListed[index.id]=true;
		final.push_back(index);
	}
  return itineraire;
}

Map::~Map(){}
