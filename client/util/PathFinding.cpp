/*
 * PathFinding.cpp
 *
 *  Created on: 29 avr. 2013
 *      Author: B�ni
 */

#include "PathFinding.h"
#include "../game/game/GameboardModel.h"

namespace util {

std::vector<CoordInt> PathFinding::getPath(CoordInt start, CoordInt goal) {
	if(outOfMap(goal) || !game::GameboardModel::getGameboard(0)[goal.x][goal.y]->getPassable()) {
		std::vector<CoordInt> r;
		return r;
	}


	int width = game::GameboardModel::getWidth();
	int height = game::GameboardModel::getHeight();
	struct node map[height * width];
	initMap(start, map, height, width);
	struct node *curNode = &map[start.y * width + start.x];
	struct node *goalNode = &map[goal.y * width + goal.x];

	std::cout << "Start is at [" << curNode->at.x << ";" << curNode->at.y << "]" << std::endl;
	std::cout << "Goal is  at [" << goalNode->at.x << ";" << goalNode->at.y << "]" << std::endl;

	while(curNode->at != goal){
		std::vector<CoordInt> neighbors(getNeighbors(curNode->at));
		for(unsigned int i = 0; i < neighbors.size(); i++){
			struct node *neighborNode = &map[neighbors.at(i).y * width + neighbors.at(i).x];
			float newCost = curNode->cost + distance(curNode->at, neighborNode->at);
			if(!neighborNode->tested && (neighborNode->cost > newCost || neighborNode->cost < 0)){
				neighborNode->cost = newCost;
				neighborNode->antecedant = curNode;
			}
		}
		curNode->tested = true;
		curNode = findLowestCost(map, height, width);
	}
	std::deque<CoordInt> path;
	assert(curNode == goalNode);
	while(curNode->at != start){
		path.push_front(curNode->at);
		curNode = curNode->antecedant;
	}
	/* On repasse d'un deque � un vector... wtf un peu */
	std::vector<CoordInt> pathVector;
	unsigned int size = path.size();
	std::cout << "Chemin pour aller de [" << curNode->at.x << ";" << curNode->at.y << "] � [" << goalNode->at.x << ";" << goalNode->at.y << "]" << std::endl;
	for(unsigned int i = 0; i < size; i++){
		pathVector.push_back(path.front());
		std::cout << "\t[" << path.front().x << ";" << path.front().y << "]" << std::endl;
		path.pop_front();
	}

	printPath(pathVector);
	return pathVector;
}

void PathFinding::initMap(CoordInt start, struct node *map, int height, int width){
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			if(start.x == x && start.y == y){
				map[y*width + x].cost = 0;
				map[y*width + x].antecedant = &map[y*width + x];
			}
			else{
				map[y*width + x].cost = -1;
				map[y*width + x].antecedant = NULL;
			}
			map[y*width + x].at = CoordInt(x,y);
			map[y*width + x].tested = false;
		}
	}
}

struct PathFinding::node* PathFinding::findLowestCost(node *map, int height, int width){
	if(!map || height <= 0 || width <= 0)
		return NULL;

	int i = 0;
	while(i < height * width && (map[i].tested || map[i].cost < 0)){ i++; }

	/* Tous les voisins ont �t� test�, ca devrait jamais arriver avant que l'objectif soit trouv� */
	if(i == height * width){
		return NULL;
	}

	struct node *n = &map[i];
	for(; i < width * height; i++){
		if(map[i].tested == false && map[i].cost < n->cost && map[i].cost >= 0){
			n = &map[i];
		}
	}

	return n;
}

std::vector<CoordInt> PathFinding::getNeighbors(CoordInt cur){
	int x = cur.x;
	int y = cur.y;

	std::vector<CoordInt> tmp;

	/* Ajout de tous les voisins probables */
	tmp.push_back(CoordInt(x, y-1));
	tmp.push_back(CoordInt(x+1, y-1));
	tmp.push_back(CoordInt(x+1, y));
	tmp.push_back(CoordInt(x+1, y+1));
	tmp.push_back(CoordInt(x, y+1));
	tmp.push_back(CoordInt(x-1, y+1));
	tmp.push_back(CoordInt(x-1, y));
	tmp.push_back(CoordInt(x-1, y-1));

	std::vector<CoordInt> voisins;

	/* Conserve uniquement les voisins se trouvant dans la map et �tant passables */
	for(unsigned int i = 0; i < tmp.size(); i++){
		CoordInt v = tmp.at(i);
		if(!outOfMap(v) && game::GameboardModel::getGameboard(0)[v.x][v.y]->getPassable())
			voisins.push_back(tmp.at(i));
	}

	return voisins;
}

/* Assume que from et to sont voisins */
float PathFinding::distance(CoordInt from, CoordInt to){
	if(from.x != to.x && from.y != to.y)
		return DIAG_COST;
	return BASIC_COST;
}

bool PathFinding::outOfMap(CoordInt coord){
	return (coord.x < 0 || coord.x >= game::GameboardModel::getWidth() ||
			coord.y < 0 || coord.y >= game::GameboardModel::getHeight());
}

void PathFinding::printPath(std::vector<CoordInt> path) {
	for(int i=0; i<15; i++) {
		for(int j=0; j<15; j++) {
			bool find = false;
			for(unsigned int k=0; k<path.size(); k++){
				if(path.at(k) == util::CoordInt(j,i))
					find = true;
			}
			if(find)
				std::cout << "X";
			else if(game::GameboardModel::getGameboard(0)[j][i]->getPassable())
				std::cout << " ";
			else
				std::cout << "#";
		}
		std::cout << std::endl;
	}
}

} /* namespace util */
