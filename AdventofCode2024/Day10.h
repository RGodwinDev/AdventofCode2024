#pragma once
#include "Day.h"
#include <vector>
#include <string>
#include <fstream>
#include <set>

class Day10 : public Day {
private:
	std::vector<std::pair<int, int>> trail2(int prev, std::pair<int, int> pos, std::vector<std::vector<int>>& map);
	std::set<std::pair<int,int>> trail(int prev,  std::pair<int, int> pos, std::vector<std::vector<int>>& map);
public:
	int run();
};