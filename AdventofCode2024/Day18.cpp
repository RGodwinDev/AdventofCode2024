#include "Day18.h"

int Day18::run() {
	int result1 = 0;
	std::pair<int, int> result2 = { -1,-1 };
	/* Day18 Being Reworked to Dijkstras/A*
	*/
	std::fstream f("day18input.txt");
	std::string s;
	while (getline(f, s)) {

	}
	//grid 0 to 70 (71 tall/wide)

	std::string result2s = "";
	result2s += std::to_string(result2.first);
	result2s += ',';
	result2s += std::to_string(result2.second);
	std::cout << std::setw(4) << "18: " << std::setw(20) << result1 << " " << std::setw(20) << result2s << std::endl;
	return 1;
}