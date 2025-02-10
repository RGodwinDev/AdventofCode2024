#pragma once
#include "Day.h"
#include <vector>
#include <fstream>
#include <string>
#include <regex>
#include <queue>
#include <set>
#include "Day18Vert.h"

class Day18 : public Day {
private:
	int bfs(std::vector<std::vector<int>>& grid);
public:
	int run();
};