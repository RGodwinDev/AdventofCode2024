#pragma once
#include <utility>

class Day16Vert {
private:
public:
	std::pair<int,int> pos;
	Day16Vert* pred;
	Day16Vert(Day16Vert* pred, int i, int j);
};