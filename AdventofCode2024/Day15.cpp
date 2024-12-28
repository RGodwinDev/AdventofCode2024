#include "Day15.h"

int Day15::run() {
	int result1 = 0, result2 = 0;
	std::ifstream f("day15input.txt");
	std::string text;
	std::pair<int, int> start;
	int j = 0;
	int walls = 0;
	std::vector<std::vector<Day15Node>> warehouse;
	//std::vector<std::vector<Day15Node>> warehouse2;

	while (getline(f, text) && walls < 2) {
		std::vector<Day15Node> wareRow;
		//std::vector<Day15Node> wareRow2;
		int sharp = 0;
		for (int i = 0; i < text.size(); ++i) {
			wareRow.push_back(Day15Node(text[i]));
			/*
			wareRow2.push_back(node);
			wareRow2.push_back(node);
			*/

			sharp += text[i] == '#';
			if (text[i] == '@') {
				start = { j,i };
			}
		}
		//std::cout << wareRow.size() << std::endl;
		warehouse.push_back(wareRow); 
		//warehouse2.push_back(wareRow2); 
		if (sharp == text.size()) {
			walls++;
		}
		j++;
	}
	/*
	std::cout << warehouse.size() << std::endl;
	std::cout << warehouse[0].size() << std::endl;
	std::cout << warehouse2.size() << std::endl;
	std::cout << warehouse2[0].size() << std::endl;
	*/

	std::string moves = "";
	while (getline(f, text)) {
		moves += text;
	}

	// < > ^ v 
	std::pair<int, int> pos = start;
	//std::cout << pos.first << " " << pos.second << std::endl;
	for (char move : moves) {
		//std::cout << move;
		if (move == '<') {
			if (checkLeft(pos, warehouse)) {
				pos.second--;
				warehouse[pos.first][pos.second].empty = true;
			}
		}
		else if (move == '>') {
			if(checkRight(pos, warehouse)) {
				pos.second++;
				warehouse[pos.first][pos.second].empty = true;
			}
		}
		else if (move == '^') {
			if (checkUp(pos, warehouse)) {
				pos.first--;
				warehouse[pos.first][pos.second].empty = true;
			}
		}
		else if (move == 'v') {
			if (checkDown(pos, warehouse)) {
				pos.first++;
				warehouse[pos.first][pos.second].empty = true;
			}
		}
		else {
			std::cout << "invalid move" << std::endl;
		}
	}
	//std::cout << std::endl;
	//get gps coords
	for (int i = 0; i < warehouse.size(); ++i) {
		for (int j = 0; j < warehouse[i].size(); ++j) {
			Day15Node n = warehouse[i][j];
			if (!(n.empty || n.rock)) {
				//std::cout << 'o';
				result1 += 100 * i;
				result1 += j;
			}
			
			/*
			else if (n.empty) {
				std::cout << '-';
			}
			else if (n.rock) {
				std::cout << '#';
			}
			*/
			
		}
		//std::cout << std::endl;
	}

	/*
	//again for warehouse 2
	for (int i = 0; i < warehouse2.size(); ++i) {
		for (int j = 0; j < warehouse2[i].size(); ++j) {
			Day15Node n = warehouse2[i][j];
			if (!(n.empty || n.rock)) {
				result2 += 100 * i;
				result2 += j;
			}
		}
	}
	*/

	std::cout << "15: " << result1 << " " << result2 << std::endl;

	return 1;
}


bool Day15::checkUp(std::pair<int, int> pos, std::vector<std::vector<Day15Node>> &warehouse) {
	
	if (warehouse[pos.first - 1][pos.second].empty) {
		//std::cout << "empty!" << std::endl;
		warehouse[pos.first - 1][pos.second].empty = false;
		return true;
	}
	if (warehouse[pos.first - 1][pos.second].rock) {
		//std::cout << "rocked" << std::endl;
		return false;
	}
	if (checkUp({ pos.first - 1 , pos.second }, warehouse)) {
		//std::cout << "pass" << std::endl;
		warehouse[pos.first][pos.second].empty = true;
		warehouse[pos.first - 1][pos.second].empty = false;
		return true;
	}
	//std::cout << "fail" << std::endl;
	return false;
}

bool Day15::checkDown(std::pair<int, int> pos, std::vector<std::vector<Day15Node>> &warehouse) {
	if (warehouse[pos.first + 1][pos.second].empty) {
		//std::cout << "empty!" << std::endl;
		warehouse[pos.first + 1][pos.second].empty = false;
		return true;
	}
	if (warehouse[pos.first + 1][pos.second].rock) {
		//std::cout << "rocked" << std::endl;
		return false;
	}
	if (checkDown({ pos.first + 1 , pos.second }, warehouse)) {
		//std::cout << "pass" << std::endl;
		warehouse[pos.first][pos.second].empty = true;
		warehouse[pos.first + 1][pos.second].empty = false;
		return true;
	}

	//std::cout << "fail" << std::endl;
	return false;
}

bool Day15::checkLeft(std::pair<int, int> pos, std::vector<std::vector<Day15Node>>& warehouse) {
	if (warehouse[pos.first][pos.second - 1].empty) {
		//std::cout << "empty!" << std::endl;
		warehouse[pos.first][pos.second - 1].empty = false;
		return true;
	}
	if (warehouse[pos.first][pos.second - 1].rock) {
		//std::cout << "rocked" << std::endl;
		return false;
	}
	if (checkLeft({ pos.first, pos.second - 1 }, warehouse)) {
		//std::cout << "pass" << std::endl;
		warehouse[pos.first][pos.second].empty = true;
		warehouse[pos.first][pos.second - 1].empty = false;
		return true;
	}

	//std::cout << "fail" << std::endl;
	return false;
}

bool Day15::checkRight(std::pair<int,int> pos, std::vector<std::vector<Day15Node>>& warehouse) {
	if (warehouse[pos.first][pos.second + 1].empty) {
		//std::cout << "empty!" << std::endl;
		warehouse[pos.first][pos.second + 1].empty = false;
		return true;
	}
	if (warehouse[pos.first][pos.second + 1].rock) {
		//std::cout << "rocked" << std::endl;
		return false;
	}
	if (checkRight({ pos.first, pos.second + 1 }, warehouse)) {
		//std::cout << "pass" << std::endl;
		warehouse[pos.first][pos.second].empty = true;
		warehouse[pos.first][pos.second + 1].empty = false;

		return true;
	}
	//std::cout << "fail" << std::endl;
	return false;
} 