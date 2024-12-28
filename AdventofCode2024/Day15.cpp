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

	int left = 0, right = 0, up = 0, down = 0;
	int al = 0, ar = 0, au = 0, ad = 0;

	// < > ^ v 
	std::pair<int, int> pos = start;

	for (char move : moves) {
		//std::cout << pos.first << " " << pos.second << std::endl;
		if (move == '<') {
			//std::cout << "left" << std::endl;
			al++;
			if (checkLeft(pos, warehouse)) {
				pos.second--;
				left++;
			}
		}
		else if (move == '>') {
			//std::cout << "right" << std::endl;
			ar++;
			if(checkRight(pos, warehouse)) {
				pos.second++;
				right++;
			}
		}
		else if (move == '^') {
			//std::cout << "up" << std::endl;
			au++;
			if (checkUp(pos, warehouse)) {
				pos.first--;
				up++;
			}
		}
		else if (move == 'v') {
			//std::cout << "down" << std::endl;
			ad++;
			if (checkDown(pos, warehouse)) {
				pos.first++;
				down++;
			}
		}
		else {
			std::cout << "invalid move" << std::endl;
		}
	}

	//get gps coords
	for (int i = 0; i < warehouse.size(); ++i) {
		//std::cout << warehouse[i].size() << std::endl;
		for (int j = 0; j < warehouse[i].size(); ++j) {
			Day15Node n = warehouse[i][j];
			if (!(n.empty || n.rock)) {
				//std::cout << 'o';
				result1 += 100 * i;
				result1 += j;
			}
			
			/*
			else if (n.empty) {
				//std::cout << '-';
			}
			else if (n.rock) {
				//std::cout << '#';
			}
			*/
			
		}
		//std::cout << std::endl;
	}

	//this just confirms, the bot is actually moving
	/*
	std::cout << au << " " << ad << std::endl;
	std::cout << up << " " << down << std::endl;
	std::cout << ar << " " << al << std::endl;
	std::cout << right << " " << left << std::endl;
	std::cout << up - down << " " << right - left << std::endl;
	std::cout << start.first << " " << start.second << std::endl;
	std::cout << pos.first << " " << pos.second << std::endl;
	*/

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