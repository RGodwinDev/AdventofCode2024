#pragma once
#include "Day.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Day11List.h"
#include "Day11ListNode.h"
#include <map>

class Day11 : public Day {
private:
	void blink(std::map<long long, long long>* m, int blinks);
public:
	int run();
};