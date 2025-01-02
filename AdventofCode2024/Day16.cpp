#include "Day16.h"

int Day16::run() {
	std::fstream f("day16input.txt");
	std::string s = "";
	std::vector<std::vector<Day16Vert>> map;
	int result1 = 0;
	int result2 = 0;
	std::pair<int, int> start;
	int i = 0;
	while (getline(f, s)) {

		std::vector<Day16Vert> v;
		for (int j = 0; j < s.size(); ++j) {
			if (s[j] == 'S') { start = {i,j}; }
			Day16Vert vert(s[j]);
			v.push_back(vert);
		}
		//make verts, put into v
		map.push_back(v);
		i++;
	}

	result1 = part1dijkstras(map, start);

	/* //print the grid
	for (std::vector<Day16Vert> line : map) {
		for (Day16Vert v : line) {
			if (v.isRock()) {
				std::cout << '#';
			}
			else if (v.isEnd()) {
				std::cout << 'E';
			}
			else {
				std::cout << '.';
			}
		}
		std::cout << '\n';
	}
	std::cout << std::endl;
	*/







	std::cout << "16: " << std::setw(20) << result1 << " " << std::setw(20) << result2 << std::endl;

	return 1; 
}


int Day16::part1dijkstras(std::vector<std::vector<Day16Vert>>& map, std::pair<int, int> start) {
	
	std::priority_queue<std::pair<int, std::pair<int, int>>> unvisited;
	//starting direction is east
	char direction = 'e';
	map[start.first][start.second].cost = 0;
	std::pair<int, int> pos = start;
	//turning = +1000 points
	//<cost, <pos>>
	unvisited.push({ 0, pos });
	while (!unvisited.empty()) {
		std::pair<int, int> cur = unvisited.top().second;
		int cost = unvisited.top().first;
		unvisited.pop();
		Day16Vert curNode = map[cur.first][cur.second];
		if (curNode.isEnd()) {
			return cost;
		}
		curNode.cost = cost;
		//std::cout << "woo" << std::endl;

	}

	




	return -1;
}