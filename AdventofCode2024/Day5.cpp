#include "Day5.h"

int Day5::run() {
	std::string text;
	std::ifstream file("./day5input.txt");

	int result1 = 0;
	int result2 = 0;
	std::vector<std::string> xmas;

	while (getline(file, text)) {
		xmas.push_back(text);
	}

	//x must be before y
	//2nd section, each line is a print job
	//make sure the print job is in the right order

	//part 1 section 1
	std::map<int, std::set<int>> lookup;
	//1175 orders
	//for (int i = 0; i < 21; ++i) { //for the test input
	for (int i = 0; i < 1176; ++i) {
		int x = stoi(xmas[i]);
		int y = stoi(xmas[i].substr(3));
		lookup[x].insert(y);
	}

	//section 2
	std::vector<std::vector<int>> incorrects;
	//for (int i = 22; i < xmas.size(); ++i) { //for the test input
	for (int i = 1177; i < xmas.size(); ++i) {
		std::vector<int> a;
		std::set<int> pages;
		bool broke = false;
		for (int j = 0; j < xmas[i].size(); j += 3) {
			int x = stoi(xmas[i].substr(j));
			a.push_back(x);
			for (int y : lookup[x]) {
				if (pages.find(y) != pages.end()) {
					broke = true;
				}
			}
			pages.insert(x);
		}
		if (!broke) {
			result1 += a[a.size()/2];
		}
		else {
			incorrects.push_back(a);
		}
	}

	//part 2
	//process the incorrects
	//bubble sort LOL
	for (std::vector<int> line : incorrects) {
		int i = 0;
		while (i < line.size()-1) {
			if (compare(line[i], line[i + 1], &lookup)) {
				//swap
				int b = line[i];
				line[i] = line[i + 1];
				line[i + 1] = b;
				i -= 2;
			}
			i = std::max(i+1, 0);
		}
		result2 += line[line.size() / 2];
	}

	std::cout << std::setw(4) << "5: " << std::setw(20) << result1 << " " << std::setw(20) << result2 << std::endl;
	return 1;
}

bool Day5::compare(int x, int y, std::map<int,std::set<int>>* m) {
	return m->at(x).find(y) != m->at(x).end();
}