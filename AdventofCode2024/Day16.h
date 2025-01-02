#pragma once
#include "Day.h"
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include "Day16Vert.h"

class Day16 : public Day {
private:
public:
	int run();
	int part1dijkstras(std::vector<std::vector<Day16Vert>>& map, std::pair<int, int> start);
};