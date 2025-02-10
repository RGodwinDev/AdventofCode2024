#include "Day18.h"

int Day18::run() {
	int result1 = 0;
	std::pair<int, int> result2 = { -1,-1 };

	std::fstream f("day18input.txt");
	std::string s;

	std::vector<std::vector<int>> grid(71, std::vector<int>(71, 0));
	int steps = 0;
	
	while (steps++ < 1024) {
		getline(f, s);
		int x = stoi(s);
		int y = stoi(s.substr(s.find(',') + 1));
		grid[x][y] = -1;
		result2 = { x,y }; //incase it's immediately done.
	}	

	result1 = bfs(grid);
	
	//part 2
	while (bfs(grid) != INT_MAX) {
		getline(f, s);
		int x = stoi(s);
		int y = stoi(s.substr(s.find(',') + 1));
		grid[x][y] = -1;
		result2 = { x,y };
	}

	std::string result2s = "";
	result2s += std::to_string(result2.first);
	result2s += ',';
	result2s += std::to_string(result2.second);
	std::cout << std::setw(4) << "18: " << std::setw(20) << result1 << " " << std::setw(20) << result2s << std::endl;
	return 1;
}

int Day18::bfs(std::vector<std::vector<int>>& grid) {
	std::vector<std::vector<int>> costs(71, std::vector<int>(71, INT_MAX));
	costs[0][0] = 0;
	std::queue<std::pair<int, int>> frontier;
	frontier.push({ 0,0 });
	
	while (!frontier.empty()) {
		std::pair<int, int> cur = frontier.front();
		frontier.pop();
		int curcost = costs[cur.first][cur.second];
		if (cur.first > 0) {					//up
			if (grid[cur.first - 1][cur.second] != -1 && costs[cur.first - 1][cur.second] > curcost + 1) {
				costs[cur.first - 1][cur.second] = curcost + 1;
				frontier.push({ cur.first - 1, cur.second });
			}
		} 
		if (cur.first < costs.size() - 1) {		//down
			if (grid[cur.first + 1][cur.second] != -1 && costs[cur.first + 1][cur.second] > curcost + 1) {
				costs[cur.first + 1][cur.second] = curcost + 1;
				frontier.push({ cur.first + 1, cur.second });
			}
		}
		if (cur.second > 0) {					//left
			if (grid[cur.first][cur.second - 1] != -1 && costs[cur.first][cur.second - 1] > curcost + 1) {
				costs[cur.first][cur.second - 1] = curcost + 1;
				frontier.push({ cur.first, cur.second - 1 });
			}
		}
		if (cur.second < costs[0].size() - 1) { //right
			if (grid[cur.first][cur.second + 1] != -1 && costs[cur.first][cur.second + 1] > curcost + 1) {
				costs[cur.first][cur.second + 1] = curcost + 1;
				frontier.push({ cur.first, cur.second + 1 });
			}
		}
	}

	return costs[70][70];
}