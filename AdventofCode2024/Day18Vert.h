#pragma once
#include <climits>

class Day18Vert {
private:
public:
	int value;
	Day18Vert* pred;
	int distance;
	Day18Vert(int value);
};