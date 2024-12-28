#include "Day12Region.h"

Day12Region::Day12Region(std::pair<int,int> pos) {
	this->perimeter = 4;
	this->sides = 4;
	this->plots.insert(pos);
}

int Day12Region::getArea() {
	return this->plots.size();
}

void Day12Region::insert(std::pair<int, int> p) {
	this->plots.insert(p);
}

bool Day12Region::contains(std::pair<int, int> p) {
	return this->plots.find(p) != this->plots.end();
}


std::set<std::pair<int, int>> Day12Region::getPlots() {
	return this->plots;
}