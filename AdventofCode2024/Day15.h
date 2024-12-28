#pragma once
#include "Day.h"
#include <fstream>
#include <string>
#include <vector>
#include "Day15Node.h"

class Day15 : public Day
{
private:
	bool checkUp(std::pair<int, int> pos, std::vector<std::vector<Day15Node>>& warehouse);
	bool checkDown(std::pair<int, int> pos, std::vector<std::vector<Day15Node>>& warehouse);
	bool checkLeft(std::pair<int, int> pos, std::vector<std::vector<Day15Node>>& warehouse);
	bool checkRight(std::pair<int, int> pos, std::vector<std::vector<Day15Node>>& warehouse);
public:
	int run();
};

