#pragma once
#include <set>

class Day12Region {
private:
	std::set<std::pair<int, int>> plots;
public:
	Day12Region(std::pair<int, int> pos);
	int perimeter;
	char crop;
	int getArea();
	int sides;
	void insert(std::pair<int, int> p);
	bool contains(std::pair<int, int>p);
	std::set<std::pair<int, int>> getPlots();
};