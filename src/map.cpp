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
		voitures.at(i).setVitesse(points.at(voitures.at(i).itineraire.at(0)).getVMinForDestIndex(voitures.at(i).itineraire.at(1)));
	}
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
		//verifier si le point a été atteint ou dépassé
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
						currentV->itineraire.erase(currentV->itineraire.begin());
						currentV->setVitesse(points.at(currentV->itineraire.at(0)).getVMinForDestIndex(currentV->itineraire.at(1)));
				}
				//verifier peloton
			}
		}
		else{	//sinon continuer a avancer
			for(unsigned j=0; j<pelotons.at(i).getPeloton().size(); j++){
				Voiture * currentV = getVoitureFromPeloton(pelotons.at(i).getPeloton().at(j));
				currentV->posX += newX;
				currentV->posY += newY;
			}
		}
	}
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
