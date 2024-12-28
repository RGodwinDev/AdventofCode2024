#include "Day25.h"

int Day25::run() {

	int result1 = 0;
	int result2 = 0;
	std::vector<std::vector<int>> keys;
	std::vector<std::vector<int>> locks;
	std::fstream f("day25input.txt");
	std::string s;
	while (getline(f, s)) {
		std::vector<int> v(5,0);
		if (s == "#####") { //lock
			for (int i = 0; i < 5; ++i) {
				getline(f, s);
				for (int j = 0; j < s.size(); ++j){
					if (s[j] == '#') {
						v[j]++;
					}
				}
			}
			locks.push_back(v);
		}
		else { //key
			for (int i = 0; i < 5; ++i) {
				getline(f, s);
				for (int j = 0; j < s.size(); ++j) {
					if (s[j] == '#') {
						v[j]++;
					}
				}
			}
			keys.push_back(v);
		}
		getline(f, s); //last ..... or #####
		getline(f, s); //blank inbetween line
	}

	for (std::vector<int> lock : locks) {
		for (std::vector<int> key : keys) {
			int passes = 0;
			for (int i = 0; i < 5; ++i) {
				if (lock[i] + key[i] <= 5) {
					passes++;
				}
			}
			if (passes == 5) {
				result1++;
			}
		}
	}


	std::cout << "25: " << result1 << " " << result2 << std::endl;
	return 1;
}