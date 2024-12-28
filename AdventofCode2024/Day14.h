#pragma once
#include "Day.h"
#include <fstream>
#include <vector>
#include <string>
#include <regex>

class Day14 : public Day {
private:
	void move(std::pair<std::pair<int, int>, std::pair<int, int>>& bot, int* width, int* height);
public:
	int run();
};