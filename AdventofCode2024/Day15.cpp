#include "Day15.h"

int Day15::run() {
	int result1 = 0, result2 = 0;
	std::ifstream f("day15input.txt");
	std::string text;
	std::pair<int, int> start;
	std::pair<int, int> start2;
	int j = 0;
	int walls = 0;
	std::vector<std::vector<Day15Node>> warehouse;
	std::vector<std::vector<char>> warehouse2;

	while (getline(f, text) && walls < 2) {
		std::vector<Day15Node> wareRow;

		std::vector<char> wareRow2;
		int sharp = 0;
		for (int i = 0; i < text.size(); ++i) {
			wareRow.push_back(Day15Node(text[i]));
			if (text[i] == '.') {
				wareRow2.push_back('.');
				wareRow2.push_back('.');
			}
			else if (text[i] == 'O') {
				wareRow2.push_back('[');
				wareRow2.push_back(']');
			}
			else if (text[i] == '#') {
				wareRow2.push_back('#');
				wareRow2.push_back('#');
			}
			else if (text[i] == '@'){
				wareRow2.push_back('.');
				start2 = { j, wareRow2.size()-1};
				wareRow2.push_back('.');
			}

			sharp += text[i] == '#';
			if (text[i] == '@') {
				start = { j,i };
			}
		}
		warehouse.push_back(wareRow); 
		warehouse2.push_back(wareRow2); 
		if (sharp == text.size()) {
			walls++;
		}
		j++;
	}

	std::string moves = "";
	while (getline(f, text)) {
		moves += text;
	}

	// < > ^ v 
	std::pair<int, int> pos = start;
	for (char move : moves) {
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

	//get gps coords
	for (int i = 0; i < warehouse.size(); ++i) {
		for (int j = 0; j < warehouse[i].size(); ++j) {
			Day15Node n = warehouse[i][j];
			if (!(n.empty || n.rock)) {
				result1 += 100 * i;
				result1 += j;
			}			
		}
	}

	//part 2
	std::pair<int, int> pos2 = start2;

	for (char move : moves) {
		if (move == '<') {
			if (warehouse2[pos2.first][pos2.second - 1] == '.') {
				pos2.second--;
			}
			else if (warehouse2[pos2.first][pos2.second - 1] == '#') {
				//can't move left
			}
			else {
				if (checkLeft2({ pos2.first, pos2.second - 1 }, warehouse2)) {
					pos2.second--;
				}
			}
		}
		else if (move == '>') {
			if (warehouse2[pos2.first][pos2.second + 1] == '.') {
				pos2.second++;
			}
			else if (warehouse2[pos2.first][pos2.second+1] == '#') {
				//can't move right
			}
			else {
				if (checkRight2({ pos2.first, pos2.second + 1 }, warehouse2)) {
					pos2.second++;
				}
			}
		}
		else if (move == '^') {
			std::set<std::pair<int, int>> lefts;
			if(checkUp2({pos2.first-1, pos2.second}, warehouse2, lefts)) {
				//if they all come back true, then move them all
				moveUp({ pos2.first - 1, pos2.second }, warehouse2, lefts);
				pos2.first--;
			}
		}
		else if (move == 'v') {
			std::set<std::pair<int, int>> lefts;
			if (checkDown2({ pos2.first + 1, pos2.second }, warehouse2, lefts)) {
				moveDown({ pos2.first + 1, pos2.second }, warehouse2, lefts);
				pos2.first++;
			}
		}
		else {
			std::cout << "invalid move" << std::endl;
		}
	
	}
	//get result of gps coords for warehouse2.
	for (int i = 0; i < warehouse2.size(); ++i) {
		for (int j = 0; j < warehouse2[i].size(); ++j) {
			if (warehouse2[i][j] == '[') {
				result2 += 100 * i;
				result2 += j;
			}
		}
	}

	/*//prints out warehouse2
	for (auto line : warehouse2) {
		for (char c : line) {
			std::cout << c;
		}
		std::cout << '\n';
	}
	std::cout << std::endl;
	*/

	std::cout << "15: " << result1 << " " << result2 << std::endl;

	return 1;
}


bool Day15::checkUp(std::pair<int, int> pos, std::vector<std::vector<Day15Node>> &warehouse) {
	
	if (warehouse[pos.first - 1][pos.second].empty) {
		warehouse[pos.first - 1][pos.second].empty = false;
		return true;
	}
	if (warehouse[pos.first - 1][pos.second].rock) {
		return false;
	}
	if (checkUp({ pos.first - 1 , pos.second }, warehouse)) {
		warehouse[pos.first][pos.second].empty = true;
		warehouse[pos.first - 1][pos.second].empty = false;
		return true;
	}
	return false;
}

bool Day15::checkDown(std::pair<int, int> pos, std::vector<std::vector<Day15Node>> &warehouse) {
	if (warehouse[pos.first + 1][pos.second].empty) {
		warehouse[pos.first + 1][pos.second].empty = false;
		return true;
	}
	if (warehouse[pos.first + 1][pos.second].rock) {
		return false;
	}
	if (checkDown({ pos.first + 1 , pos.second }, warehouse)) {
		warehouse[pos.first][pos.second].empty = true;
		warehouse[pos.first + 1][pos.second].empty = false;
		return true;
	}

	//std::cout << "fail" << std::endl;
	return false;
}

bool Day15::checkLeft(std::pair<int, int> pos, std::vector<std::vector<Day15Node>>& warehouse) {
	if (warehouse[pos.first][pos.second - 1].empty) {
		warehouse[pos.first][pos.second - 1].empty = false;
		return true;
	}
	if (warehouse[pos.first][pos.second - 1].rock) {
		return false;
	}
	if (checkLeft({ pos.first, pos.second - 1 }, warehouse)) {
		warehouse[pos.first][pos.second].empty = true;
		warehouse[pos.first][pos.second - 1].empty = false;
		return true;
	}
	return false;
}

bool Day15::checkRight(std::pair<int,int> pos, std::vector<std::vector<Day15Node>>& warehouse) {
	if (warehouse[pos.first][pos.second + 1].empty) {
		warehouse[pos.first][pos.second + 1].empty = false;
		return true;
	}
	if (warehouse[pos.first][pos.second + 1].rock) {
		return false;
	}
	if (checkRight({ pos.first, pos.second + 1 }, warehouse)) {
		warehouse[pos.first][pos.second].empty = true;
		warehouse[pos.first][pos.second + 1].empty = false;

		return true;
	}
	return false;
} 

bool Day15::checkUp2(std::pair<int, int> pos, std::vector<std::vector<char>>& warehouse, std::set<std::pair<int,int>> &lefts) {
	if (warehouse[pos.first][pos.second] == '.') {
		return true;
	}
	if (warehouse[pos.first][pos.second] == '#') {
		return false;
	}

	if (warehouse[pos.first][pos.second] == '[') {
		lefts.insert({ pos });
		return checkUp2({ pos.first - 1, pos.second }, warehouse, lefts) && checkUp2({ pos.first - 1, pos.second + 1 }, warehouse, lefts);
	}
	else { // == ']'
		lefts.insert({ pos.first, pos.second - 1 });
		return checkUp2({ pos.first - 1, pos.second }, warehouse, lefts) && checkUp2({ pos.first - 1, pos.second - 1 }, warehouse, lefts);
	}
}
bool Day15::checkDown2(std::pair<int, int> pos, std::vector<std::vector<char>>& warehouse, std::set<std::pair<int, int>>& lefts) {
	if (warehouse[pos.first][pos.second] == '.') {
		return true;
	}
	if (warehouse[pos.first][pos.second] == '#') {
		return false;
	}

	if (warehouse[pos.first][pos.second] == '[') {
		lefts.insert({ pos });
		return checkDown2({ pos.first + 1, pos.second }, warehouse, lefts) && checkDown2({ pos.first + 1, pos.second + 1 }, warehouse, lefts);
	}
	else { // == ']'
		lefts.insert({ pos.first, pos.second - 1 });
		return checkDown2({ pos.first + 1, pos.second }, warehouse, lefts) && checkDown2({ pos.first + 1, pos.second - 1 }, warehouse, lefts);
	}
}
bool Day15::checkLeft2(std::pair<int, int> pos, std::vector<std::vector<char>>& warehouse) {
	//we know the current position is a right side box
	//check 2 to the left
	if (warehouse[pos.first][pos.second - 2] == '.') {
		warehouse[pos.first][pos.second - 2] = warehouse[pos.first][pos.second - 1];
		warehouse[pos.first][pos.second - 1] = warehouse[pos.first][pos.second];
		warehouse[pos.first][pos.second] = '.';
		return true;
	}
	else if (warehouse[pos.first][pos.second - 2] == '#') {
		return false;
	}
	else if (checkLeft2({ pos.first, pos.second - 2 }, warehouse)) {
		warehouse[pos.first][pos.second - 2] = warehouse[pos.first][pos.second - 1];
		warehouse[pos.first][pos.second - 1] = warehouse[pos.first][pos.second];
		warehouse[pos.first][pos.second] = '.';
		return true;
	}
	return false;
}
bool Day15::checkRight2(std::pair<int, int> pos, std::vector<std::vector<char>>& warehouse) {
	if (warehouse[pos.first][pos.second + 2] == '.') {
		warehouse[pos.first][pos.second + 2] = warehouse[pos.first][pos.second + 1];
		warehouse[pos.first][pos.second + 1] = warehouse[pos.first][pos.second];
		warehouse[pos.first][pos.second] = '.';
		return true;
	}
	else if (warehouse[pos.first][pos.second + 2] == '#') {
		return false;
	}
	else if (checkRight2({ pos.first, pos.second + 2 }, warehouse)) {
		warehouse[pos.first][pos.second + 2] = warehouse[pos.first][pos.second + 1];
		warehouse[pos.first][pos.second + 1] = warehouse[pos.first][pos.second];
		warehouse[pos.first][pos.second] = '.';
		return true;
	}
	return false;
}

void Day15::moveUp(std::pair<int, int> pos, std::vector<std::vector<char>>& warehouse, std::set<std::pair<int, int>>& lefts) {
	//takes all the positions in left, turns them into '.'s
	for (std::pair<int, int> left : lefts) {
		warehouse[left.first][left.second] = '.';
		warehouse[left.first][left.second + 1] = '.';
	}
	//then make the boxes again, just shifted up 1.
	//if we were using actual objects (video game enemies?) this would be bad, as it effectively destroys the 'object', the []box, and creates new ones each time.
	for (std::pair<int, int> left : lefts) {
		warehouse[left.first-1][left.second] = '[';
		warehouse[left.first - 1][left.second + 1] = ']';
	}
	return;
}

void Day15::moveDown(std::pair<int, int> pos, std::vector<std::vector<char>>& warehouse, std::set<std::pair<int, int>>& lefts) {
	for (std::pair<int, int> left : lefts) {
		warehouse[left.first][left.second] = '.';
		warehouse[left.first][left.second + 1] = '.';
	}
	for (std::pair<int, int> left : lefts) {
		warehouse[left.first + 1][left.second] = '[';
		warehouse[left.first + 1][left.second + 1] = ']';
	}
	return;
}