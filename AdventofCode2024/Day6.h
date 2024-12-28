#pragma once
#include "Day.h"
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <map>

class Day6 : public Day {
private:
	enum class direction { north, east, south, west };
	bool loopcheck(std::pair<int, int> pos, Day6::direction a, std::vector<std::string>& xmas, std::map<Day6::direction, std::pair<int, int>>& m);
public:
	int run();
};