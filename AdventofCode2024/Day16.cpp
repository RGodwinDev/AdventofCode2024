#include "Day16.h"

int Day16::run() {
	std::fstream f("day16input.txt");
	std::string s = "";
	std::vector<std::vector<Day16Vert>> map;
	int result1 = 0;
	int result2 = 0;
	while (getline(f, s)) {
		std::vector<Day16Vert> v;
		//make verts, put into v
		map.push_back(v);
	}
	/*
	std::cout << map[map.size() - 2][1] << std::endl;
	std::cout << map[1][map[1].size() - 2] << std::endl;
	*/
	/*
	for (std::string s : map) {
		std::cout << s << std::endl;
	}
	*/


	std::cout << "16: " << result1 << " " << result2 << std::endl;

	return 1; 
}

int part1dijkstras(std::vector<std::string> map, std::pair<int, int> start) {
	std::queue<std::pair<int, int>> unvisited;
	return 1;
}