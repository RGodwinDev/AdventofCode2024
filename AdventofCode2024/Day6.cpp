#include "Day6.h"

int Day6::run() {
	int result1 = 1;
	int result2 = 0;
	
	std::string text;
	std::ifstream file("./day6input.txt");

	std::vector<std::string> xmas;

	while (getline(file, text)) {
		xmas.push_back(text);
	}
	Day6::direction a = Day6::direction::north;
	//find the guards position
	std::pair<int, int> startPos;
	for (int i = 0; i < xmas.size(); ++i) {
		for (int j = 0; j < xmas[i].size(); ++j) {
			if (xmas[i][j] == '^') {
				startPos = { i,j };
			}
		}
	}
	std::pair<int, int> pos = startPos;
	xmas[pos.first][pos.second] = 'x';

	//visited is places we've checked for being a rock
	std::set<std::pair<int, int>> visited;
	//add start position to visited, so we don't check it
	visited.insert(startPos);

	//direction transforms
	std::map<Day6::direction, std::pair<int,int>> m;
	m[Day6::direction::north] = { -1, 0 };
	m[Day6::direction::east] = { 0, 1 };
	m[Day6::direction::south] = { 1, 0 };
	m[Day6::direction::west] = { 0,-1 };

	//while position is inbounds
	while (pos.first >= 0 && pos.first < xmas.size() && pos.second >= 0 && pos.second < xmas[0].size()) {
		std::pair<int, int> transform = m[a];
		std::pair<int, int> next = { pos.first + transform.first , pos.second + transform.second };

		//if we're on the edge, and going that direction, just go off the edge.
		if ((a == Day6::direction::north && pos.first == 0) ||
			(a == Day6::direction::east && pos.second == xmas[0].size() - 1) ||
			(a == Day6::direction::south && pos.first == xmas.size() - 1) ||
			(a == Day6::direction::west && pos.second == 0)) {
			pos = next;
		} 
		else if (xmas[next.first][next.second] == '#') {
			//change direction, position stays the same
			a = (Day6::direction)(((int)a + 1) % 4);
		}
		else {
			if (xmas[next.first][next.second] != 'x') {
				//haven't been here before, +1 to path length, mark it.
				result1++;
				xmas[next.first][next.second] = 'x';
			}

			if (visited.find(next) == visited.end()) {
				if (loopcheck(pos, a, xmas, m)) {
					//it looped, and we know it's a unique position because we havent visited before.
					result2++;
				}
				visited.insert(next);
			}
			pos = next;
		}
	}
	
	std::cout << "6: " << result1 << " " << result2 << std::endl;

	return 1;
}

//returns true if it ends in a loop
bool Day6::loopcheck(std::pair<int,int> pos, Day6::direction a, std::vector<std::string> &xmas, std::map<Day6::direction,std::pair<int,int>> &m) {
	//calc where to put the box (infront of us)
	std::pair<int, int> transform = m[a];
	std::pair<int, int> placedBox = { pos.first + transform.first, pos.second + transform.second };

	//place the box (infront of us)
	xmas[placedBox.first][placedBox.second] = '#';

	//turn (because there's a rock infront of us)
	a = (Day6::direction)(((int)a + 1) % 4);
	transform = m[a];
	
	//use these to figure out if we're looping.
	std::set<std::pair<int, int>> north;
	std::set<std::pair<int, int>> east;
	std::set<std::pair<int, int>> south;
	std::set<std::pair<int, int>> west;
	std::vector<std::set<std::pair<int, int>>> maps = { north, east, south, west };

	while (pos.first >= 0 && pos.first < xmas.size() && pos.second >= 0 && pos.second < xmas[0].size()) {

		//we're goin off the edge, not a loop
		if ((a == Day6::direction::north && pos.first == 0) ||
			(a == Day6::direction::east && pos.second == xmas[0].size() - 1) ||
			(a == Day6::direction::south && pos.first == xmas.size() - 1) ||
			(a == Day6::direction::west && pos.second == 0)) {
			break;
		}

		//it's a loop!
		if (maps[(int)a].find(pos) != maps[(int)a].end()) {
			xmas[placedBox.first][placedBox.second] = 'x';
			return true;
		}

		//not a loop, insert cur pos into the map
		maps[(int)a].insert(pos);

		//if forward is a rock, change direction
		if (xmas[pos.first + transform.first][pos.second + transform.second] == '#') {
			a = (Day6::direction)(((int)a + 1) % 4);
			transform = m[a];
		}
		else { //otherwise, move forward
			pos.first += transform.first;
			pos.second += transform.second;
		}
	}

	//if we got here, we exited the map
	//remove the placed box
	xmas[placedBox.first][placedBox.second] = 'x';
	return false;
}
