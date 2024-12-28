#pragma once
#include "Day.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

class Day5 : public Day
{
private:
	bool compare(int x, int y, std::map<int,std::set<int>>* m);
public:
	int run();
};
