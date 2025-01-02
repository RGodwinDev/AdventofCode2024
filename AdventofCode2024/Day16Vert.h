#pragma once
#include <utility>
#include <climits>
class Day16Vert {
private:
	bool rock;
	bool end;
public:
	int cost = INT_MAX;
	std::pair<int, int> pred = { -1, -1 };
	Day16Vert(char c);
	bool isRock();
	bool isEnd();
};