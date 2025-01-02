#include "Day4.h"


int Day4::run() {
	std::string text;
	std::ifstream file("./day4input.txt");

	int result1 = 0;
	int result2 = 0;
	std::vector<std::string> xmas;

	while (getline(file, text)) {
		xmas.push_back(text);
	}
	//part 1
	for (int i = 0; i < xmas.size(); ++i) {
		for(int j = 0; j < xmas[i].size(); ++j){
			if (xmas[i][j] == 'X') {
				//get all 8 directions

				//NW
				if (i > 2 && j > 2
					&& xmas[i-1][j-1] == 'M'
					&& xmas[i-2][j-2] == 'A'
					&& xmas[i-3][j-3] == 'S') {
					result1++;
				}
				//N
				if (i > 2
					&& xmas[i-1][j] == 'M'
					&& xmas[i-2][j] == 'A'
					&& xmas[i-3][j] == 'S') {
					result1++;
				}
				//NE
				if (i > 2 && j < xmas[i].size() - 3
					&& xmas[i-1][j+1] == 'M'
					&& xmas[i-2][j+2] == 'A'
					&& xmas[i-3][j+3] == 'S') {
						result1++;
				}
				//E
				if (j < xmas[i].size() - 3
					&& xmas[i][j+1] == 'M'
					&& xmas[i][j+2] == 'A'
					&& xmas[i][j+3] == 'S') {
					result1++;
				}
				//SE
				if (i < xmas.size() - 3 && j < xmas[i].size() - 3
					&& xmas[i+1][j+1] == 'M'
					&& xmas[i+2][j+2] == 'A'
					&& xmas[i+3][j+3] == 'S') {
					result1++;
				}
				//S
				if (i < xmas.size() - 3
					&& xmas[i+1][j] == 'M'
					&& xmas[i+2][j] == 'A'
					&& xmas[i+3][j] == 'S') {
					result1++;
				}
				//SW
				if (i < xmas.size() - 3 && j > 2
					&& xmas[i+1][j-1] == 'M'
					&& xmas[i+2][j-2] == 'A'
					&& xmas[i+3][j-3] == 'S') {
					result1++;
				}
				//W
				if (j > 2
					&& xmas[i][j-1] == 'M'
					&& xmas[i][j-2] == 'A'
					&& xmas[i][j-3] == 'S') {
					result1++;
				}
			}
		}
	}

	//part 2
	std::set<std::pair<int, int>> diagupdown;
	std::set<std::pair<int, int>> diagdownup;

	for (int i = 0; i < xmas.size(); ++i) {
		for (int j = 0; j < xmas[i].size(); ++j) {
			if (xmas[i][j] == 'M') {
				//get 4 diag directions

				//NW
				if (i > 1 && j > 1
					&& xmas[i - 1][j - 1] == 'A'
					&& xmas[i - 2][j - 2] == 'S') {
					diagupdown.insert({ i - 2, j - 2 }); 
				}
				//NE
				if (i > 1 && j < xmas[i].size() - 2
					&& xmas[i - 1][j + 1] == 'A'
					&& xmas[i - 2][j + 2] == 'S') {
					diagdownup.insert({ i, j });
				}
				//SE
				if (i < xmas.size() - 2 && j < xmas[i].size() - 1
					&& xmas[i + 1][j + 1] == 'A'
					&& xmas[i + 2][j + 2] == 'S') {
					diagupdown.insert({ i,j });
				}
				//SW
				if (i < xmas.size() - 2 && j > 1
					&& xmas[i + 1][j - 1] == 'A'
					&& xmas[i + 2][j - 2] == 'S') {
					diagdownup.insert({ i + 2, j - 2 });
				}
			}
		}
	}

	for (std::pair<int, int> p : diagupdown) {
		//check if theres a viable x in diagdownup
		if (diagdownup.find({ p.first+2, p.second }) != diagdownup.end()) {
			result2++;
		}
	}

	std::cout << std::setw(4) << "4: " << std::setw(20) << result1 << " " << std::setw(20) << result2 << std::endl;
	return 1;
}