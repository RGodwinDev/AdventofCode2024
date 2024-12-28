#include "Day8.h"

int Day8::run() {
	std::string text;
	std::ifstream file("./day8input.txt");

	int result1 = 0;
	int result2 = 0;
	std::vector<std::string> xmas;

	while (getline(file, text)) {
		xmas.push_back(text);
	}

	std::map<char, std::vector<std::pair<int, int>>> antennas;
	for (int i = 0; i < xmas.size(); ++i) {
		for (int j = 0; j < xmas[i].size(); ++j) {
			if (xmas[i][j] != '.') {
				antennas[xmas[i][j]].push_back({ i,j });
			}
		}
	}

	std::set<std::pair<int, int>> antinodes;
	for (std::pair<char, std::vector<std::pair<int,int>>> a : antennas) {
		std::vector < std::pair<int, int>> v = a.second;
		for (int i = 0; i < a.second.size()-1; ++i) {
			for (int j = i + 1; j < a.second.size(); ++j) {
				std::pair<int, int> dist = { v[i].first - v[j].first, v[i].second - v[j].second };
				std::pair<int, int> x = { v[i].first + dist.first, v[i].second + dist.second };
				if (x.first >= 0 && x.first < xmas.size() && x.second >= 0 && x.second < xmas[i].size()) {
					antinodes.insert(x);
				}
				std::pair<int,int> y = { v[j].first - dist.first, v[j].second - dist.second };
				if (y.first >= 0 && y.first < xmas.size() && y.second >= 0 && y.second < xmas[i].size()) {
					antinodes.insert(y);
				}
			}
		}
	}
	result1 = antinodes.size();

	//part 2
	std::set<std::pair<int, int>> antinodes2;
	for (std::pair<char, std::vector<std::pair<int, int>>> a : antennas) {
		std::vector < std::pair<int, int>> v = a.second;
		for (int i = 0; i < a.second.size(); ++i) {
			//add the antennas positions as well
			antinodes2.insert({ v[i].first, v[i].second });
			for (int j = i + 1; j < a.second.size(); ++j) {
				std::pair<int, int> dist = { v[i].first - v[j].first, v[i].second - v[j].second };

				std::pair<int, int> x = { v[i].first + dist.first, v[i].second + dist.second };
				while (x.first >= 0 && x.first < xmas.size() && x.second >= 0 && x.second < xmas[i].size()) {
					antinodes2.insert(x);
					x = { x.first + dist.first, x.second + dist.second };
				}

				std::pair<int, int> y = { v[j].first - dist.first, v[j].second - dist.second };
				while (y.first >= 0 && y.first < xmas.size() && y.second >= 0 && y.second < xmas[i].size()) {
					antinodes2.insert(y);
					y = { y.first - dist.first, y.second - dist.second };
				}
			}
		}
	}
	result2 = antinodes2.size();

	std::cout << "8: " << result1 << " " << result2 << std::endl;
	return 1;
}