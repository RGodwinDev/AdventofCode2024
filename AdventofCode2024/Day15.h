#pragma once
#include "Day.h"
#include <fstream>
#include <string>
#include <vector>
#include "Day15Node.h"
#include <set>
class Day15 : public Day
{
private:
	bool checkUp(std::pair<int, int> pos, std::vector<std::vector<Day15Node>>& warehouse);
	bool checkDown(std::pair<int, int> pos, std::vector<std::vector<Day15Node>>& warehouse);
	bool checkLeft(std::pair<int, int> pos, std::vector<std::vector<Day15Node>>& warehouse);
	bool checkRight(std::pair<int, int> pos, std::vector<std::vector<Day15Node>>& warehouse);
	bool checkUp2(std::pair<int, int> pos, std::vector<std::vector<char>> &warehouse, std::set<std::pair<int,int>> &lefts);
	bool checkDown2(std::pair<int, int> pos, std::vector<std::vector<char>>& warehouse, std::set<std::pair<int, int>>& lefts);
	bool checkLeft2(std::pair<int, int> pos, std::vector<std::vector<char>>& warehouse);
	bool checkRight2(std::pair<int, int> pos, std::vector<std::vector<char>>& warehouse);
	void moveUp(std::pair<int, int> pos, std::vector<std::vector<char>>& warehouse, std::set<std::pair<int, int>>& lefts);
	void moveDown(std::pair<int, int> pos, std::vector<std::vector<char>>& warehouse, std::set<std::pair<int, int>>& lefts);
public:
	int run();
};

