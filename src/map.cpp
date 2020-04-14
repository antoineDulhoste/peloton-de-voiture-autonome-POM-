#include "map.h"

Map::Map(int nbPoints, int larg, int lon):nbPoints(nbPoints), largeur(larg),longueur(lon){
	for(int i = 0; i<nbPoints; i++){
		int x= rand()%lon;
		int y= rand()%larg;
		points.push_back(Point(i,x,y));
		std::cout<<"point x:"<<x<<" y:"<<y<<std::endl;
	}
}

Map::Map(std::vector<Point> m,int larg,int lon): points(m),largeur(larg),longueur(lon){
	nbPoints = m.size();
}

std::vector<Point> Map::getPoints(){
	return this->points;
}
void Map::setPoints(std::vector<Point> m){
	this->points=m;
}

int Map::getLargeur(){return this->largeur;}
int Map::getLongueur(){return this->longueur;}
void Map::setLargeur(int larg){this->largeur=larg;}
void Map::setLongueur(int lon){this->longueur= lon;}

void Map::setRoute(int index1, int index2){
	double cost = costForIndexToIndex(index1, index2);
	points.at(index1).addDestination(index2, cost);
	points.at(index2).addDestination(index1, cost);
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
