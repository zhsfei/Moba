/*
 * PathFinding.cpp
 *
 *  Created on: 29 avr. 2013
 *      Author: B�ni
 */

#include "PathFinding.h"

namespace util {

//pathfinding
std::vector<Coordinates> PathFinding::getPath(Coordinates start, Coordinates goal) {
	std::queue<Coordinates> vector;
	std::map<Coordinates, Coordinates> parent;
	parent[start] = start;
	Coordinates curr = start;
	int counter = 0;
	boost::timer t;
	while(curr != goal) {
		std::vector<Coordinates> tmp;
		for(int i=-1; i<2; i++) {
			for(int j=-1; j<2; j++) {
				if(curr.x+i >= 0 && curr.x+i < game::GameboardModel::getWidth() &&
						curr.y+j >= 0 && curr.y+j < game::GameboardModel::getHeight() &&
						game::GameboardModel::getGameboard(0)[curr.x+i][curr.y+j]->getPassable()) {
					counter++;
					Coordinates coord(curr.x+i, curr.y+j);
					if(parent.find(coord) == parent.end()) {
						tmp.push_back(coord);
						parent[coord] = curr;
					}
				}
			}
		}
		//bad tri
		for(unsigned int i=0; i<tmp.size()-1;i++) {
			for(unsigned int j=i; j<tmp.size()-1; j++) {
				if((tmp.at(j).x > goal.x ? tmp.at(j).x - goal.x : goal.x - tmp.at(j).x)
    				+(tmp.at(j).y > goal.y ? tmp.at(j).y - goal.y : goal.y - tmp.at(j).y)
    				< (tmp.at(j+1).x > goal.x ? tmp.at(j+1).x - goal.x : goal.x - tmp.at(j+1).x)
    				+(tmp.at(j+1).y > goal.y ? tmp.at(j+1).y - goal.y : goal.y - tmp.at(j+1).y)) {
					/*
					Coordinates c = tmp.at(i);
					tmp.erase(tmp.begin()+i);
					tmp.insert(tmp.begin()+i+1, c);*/
				}
			}
		}

		for(unsigned int i=0; i<tmp.size(); i++)
			vector.push(tmp.at(i));
		curr = vector.front();
		vector.pop();
	}
	std::cout << "COUNTER : " << counter << std::endl;
	std::cout << "TIMER : " << t.elapsed() << std::endl;
	std::vector<Coordinates> r;
	while(parent[curr] != curr) {
		r.push_back(curr);
		curr = parent[curr];
	}
	return r;
}

void PathFinding::printPath(std::vector<Coordinates> path) {
	for (std::vector<Coordinates>::iterator it = path.begin() ; it != path.end() ; ++it)
		std::cout << (*it).toString() << std::endl;
}

} /* namespace util */
