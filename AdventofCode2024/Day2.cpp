#include "Day2.h"

int Day2::run() {
	std::string text;
	std::ifstream file("./day2input.txt");
	
	std::vector<std::vector<int>> lines;

	while (getline(file, text)) {
		std::stringstream ss(text);
		std::string word;
		std::vector<int> v;
		while (ss >> word) {
			v.push_back(stoi(word));
		}
		lines.push_back(v);
	}

	//part 1
	int safeA = 0;
	
	for (std::vector<int> line : lines) {
		int broke = 0;
		//check if increasing
		for (int i = 1; i < line.size(); ++i) {
			int x = line[i] - line[i - 1];
			if (x > 3 || x < 1) {
				broke++;
			}
		}
		if (broke == 0) { 
			safeA++;
			continue; 
		}
		 

		//check if decreasing
		broke = 0;
		for (int i = 1; i < line.size(); ++i) {
			int x = line[i-1] - line[i];
			if (x > 3 || x < 1) {
				broke++;
			}
		}
		if (broke == 0) {
			safeA++; 
		}
	}
	
	
	//part 2
	int safeB = 0;
	
	for (std::vector<int> line : lines) {

		//check for increasing
		std::vector<int> copy = line;
		int pos = 0;
		int issues = 0;
		for (int i = 0; i < copy.size() - 1; ++i) {
			int diff = copy[i + 1] - copy[i];
			if (diff < 1 || diff > 3) {
				issues++;
				pos = i;
				break;
			}
		}
		//if theres no issues the line is good
		if (issues == 0) {
			safeB++;
			continue;
		}
		
		//if there were, erase element at pos, and check again
		issues = 0;
		copy.erase(copy.begin()+pos);
		for (int i = 0; i < copy.size() - 1; ++i) {
			int diff = copy[i + 1] - copy[i];
			if (diff < 1 || diff > 3) {
				issues++;
				break;
			}
		}
		if (issues == 0) {
			safeB++;
			continue;
		}

		//if theres still an issue, check by erasing at pos+1 instead
		copy = line;
		copy.erase(copy.begin() + pos + 1);
		issues = 0;
		for (int i = 0; i < copy.size() - 1; ++i) {
			int diff = copy[i + 1] - copy[i];
			if (diff < 1 || diff > 3) {
				issues++;
				break;
			}
		}
		if (issues == 0) {
			safeB++;
			continue;
		}

		//now check for decreasing order
		copy = line;
		pos = 0;
		issues = 0;
		for (int i = 0; i < copy.size() - 1; ++i) {
			int diff = copy[i + 1] - copy[i];
			if (diff > -1 || diff < -3) {
				issues++;
				pos = i;
				break;
			}
		}
		//if theres no issues the line is good
		if (issues == 0) {
			safeB++;
			continue;
		}

		//if there were, erase element at pos, and check again
		issues = 0;
		copy.erase(copy.begin() + pos);
		for (int i = 0; i < copy.size() - 1; ++i) {
			int diff = copy[i + 1] - copy[i];
			if (diff > -1 || diff < -3) {
				issues++;
				break;
			}
		}
		if (issues == 0) {
			safeB++;
			continue;
		}

		//if theres still an issue, check by erasing at pos+1 instead
		copy = line;
		copy.erase(copy.begin() + pos + 1);
		issues = 0;
		for (int i = 0; i < copy.size() - 1; ++i) {
			int diff = copy[i + 1] - copy[i];
			if (diff > -1 || diff < -3) {
				issues++;
				break;
			}
		}
		if (issues == 0) {
			safeB++;
			continue;
		}
	}
	
	std::cout << std::setw(4) << "2: " << std::setw(20) << safeA << " " << std::setw(20) << safeB << std::endl;

	return 1;
}