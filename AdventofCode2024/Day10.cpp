#include "Day10.h"

int Day10::run() {
	std::string text;
	std::ifstream file("./day10input.txt");

	int result1 = 0;
	int result2 = 0;
	std::vector<std::vector<int>> map;

	while (getline(file, text)) {
		std::vector<int> line;
		for (char c : text) {
			line.push_back(int(c - '0'));
		}
		map.push_back(line);
	}

	//topographic map
	//lowpoints at 0
	//highpoints at 9
	//all 'paths' are gradual upwards (increase from 0-9 by 1 each step)
	//how many tops are reachable from each trailhead
	//recursively check all directions for the trail, upon reaching the top, return the position.
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			std::set<std::pair<int, int>> trailends;
			if (map[i][j] == 0) {
				if (i > 0) {
					for (std::pair<int, int> t : trail(0, { i - 1, j }, map)) {
						trailends.insert(t);
					}
				}
				if (i < map.size() - 1) {
					for (std::pair<int, int> t : trail(0, { i + 1, j }, map)) {
						trailends.insert(t);
					}
				}
				if (j > 0) {
					for (std::pair<int, int> t : trail(0, { i, j - 1 }, map)) {
						trailends.insert(t);
					}
				}
				if (j < map[0].size() - 1) {
					for (std::pair<int, int> t : trail(0, { i, j + 1 }, map)) {
						trailends.insert(t);
					}
				}
			}
			result1 += trailends.size();
		}
	}

	//part 2, how many distinct trails are there
	//literally the same thing, but use vectors instead of sets
	//we don't even need the vectors in the end, just how big they are.
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			if (map[i][j] == 0) {
				if (i > 0) {
					result2 += trail2(0, { i - 1, j }, map).size();
				}
				if (i < map.size() - 1) {
					result2 += trail2(0, { i + 1, j }, map).size();
				}
				if (j > 0) {
					result2 += trail2(0, { i, j - 1 }, map).size();
				}
				if (j < map[0].size() - 1) {
					result2 += trail2(0, { i, j + 1 }, map).size();
				}
			}
		}
	}


	std::cout << "10: " << result1 << " " << result2 << std::endl;
	return 1;
}

std::set<std::pair<int,int>> Day10::trail(int prev, std::pair<int, int> pos, std::vector<std::vector<int>>& map) {
	if (map[pos.first][pos.second] != prev + 1) {
		return {};
	}
	if (map[pos.first][pos.second] == 9) {
		return { pos }; }
	//if it's 0, just continue on with the rest
	std::set<std::pair<int, int>> result = {};
	if (pos.first > 0) {
		for (std::pair<int, int> p : trail(prev + 1, { pos.first - 1, pos.second }, map)) {
			result.insert(p);
		}
	}
	if (pos.first < map.size() - 1) {
		for (std::pair<int, int> p : trail(prev + 1, { pos.first + 1, pos.second }, map)) {
			result.insert(p);
		}
	}
	if (pos.second > 0) {
		for (std::pair<int, int> p : trail(prev + 1, { pos.first, pos.second - 1 }, map)) {
			result.insert(p);
		}
	}
	if (pos.second < map[0].size()-1) {
		for (std::pair<int, int> p : trail(prev + 1, { pos.first, pos.second + 1 }, map)) {
			result.insert(p);
		}
	}

	return result;
}

std::vector<std::pair<int, int>> Day10::trail2(int prev, std::pair<int, int> pos, std::vector<std::vector<int>>& map) {
	if (map[pos.first][pos.second] != prev + 1) {
		return {};
	}
	if (map[pos.first][pos.second] == 9) {
		return { pos };
	}
	//if it's 0, just continue on with the rest
	std::vector<std::pair<int, int>> result = {};
	if (pos.first > 0) {
		for (std::pair<int, int> p : trail2(prev + 1, { pos.first - 1, pos.second }, map)) {
			result.push_back(p);
		}
	}
	if (pos.first < map.size() - 1) {
		for (std::pair<int, int> p : trail2(prev + 1, { pos.first + 1, pos.second }, map)) {
			result.push_back(p);
		}
	}
	if (pos.second > 0) {
		for (std::pair<int, int> p : trail2(prev + 1, { pos.first, pos.second - 1 }, map)) {
			result.push_back(p);
		}
	}
	if (pos.second < map[0].size() - 1) {
		for (std::pair<int, int> p : trail2(prev + 1, { pos.first, pos.second + 1 }, map)) {
			result.push_back(p);
		}
	}

	return result;
}