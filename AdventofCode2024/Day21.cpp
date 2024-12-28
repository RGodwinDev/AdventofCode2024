#include "Day21.h"

int Day21::run() {
	int result1 = 0;
	int result2 = 0;

	/*
		7 8 9
		4 5 6
		1 2 3
		  0 A

		  ^ A
		< V >
	*/
	std::vector<std::string> codes;

	std::fstream f("day21input.txt");
	std::string text;
	while (getline(f, text)) {
		codes.push_back(text);
	}


	std::cout << "21: " << result1 << " " << result2 << std::endl;
	return 1;
}