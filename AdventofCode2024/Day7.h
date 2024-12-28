#pragma once
#include "Day.h"
#include <vector>
#include <string>
#include <fstream>
#include <regex>

class Day7 : public Day {
private:
	bool calc(std::vector<long long> &v, int pos, long long target, long long cur);
	bool calc2(std::vector<long long>& v, int pos, long long target, long long cur);
public:
	int run();
};