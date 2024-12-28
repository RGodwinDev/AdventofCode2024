#pragma once
#include "Day.h"
#include <fstream>
#include <vector>
#include <string>
#include "./Library/eigen-3.4.0/Eigen/Dense"


class Day13 : public Day {
private:

	bool isNearInt(Eigen::Vector2d x);
public:
	int run();
};