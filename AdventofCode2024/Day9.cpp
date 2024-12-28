#include "Day9.h"

int Day9::run() {
	std::string text;
	std::ifstream file("./day9input.txt");

	long long result1 = 0;
	long long result2 = 0;
	std::string xmas;

	getline(file, text);
	xmas = text;
	std::vector<int> disk;
	std::vector<int> empty;
	std::vector<int> notempty;

	for (int i = 0; i < xmas.size(); i += 2) {
		int x = xmas[i]-'0';
		notempty.push_back(disk.size());
		notempty.push_back(x);
		for (int j = 0; j < x; ++j) {
			disk.push_back(i / 2);
		}
		//assumes the input is even sized
		int y = xmas[i + 1]-'0';
		//insert position and size of empty space
		empty.push_back(disk.size());
		empty.push_back(y);
		for (int j = 0; j < y; ++j) {
			disk.push_back(-1);
		}
	}
	std::vector<int> disk2 = disk;

	//part 1
	int l = 0;
	int r = disk.size() - 1;
	while (l < r) {
		if(disk[l] != -1){			l++; }
		else if (disk[r] == -1) {	r--; }
		else {
			disk[l] = disk[r];
			disk[r] = -1;
			l++;
			r--;
		}
	}
	
	//part2
	//Search the empty vec for a spot big enough
	//right to left on notempty
	for (int i = notempty.size()-2; i >= 0; i -= 2) {
		int pos = notempty[i];
		int size = notempty[i + 1];
		for (int j = 0; empty[j] < pos; j+=2) {
			//check each empty position from left to right
			int emptyPos = empty[j];
			int emptySize = empty[j + 1];
			if (emptyPos < pos && emptySize >= size) {
				//if theres a large enough empty position, move.
				for (int k = 0; k < size; k++) {
					disk2[emptyPos + k] = disk2[pos + k];
					disk2[pos + k] = -1;
				}
				
				empty[j] += size;
				empty[j + 1] -= size;
				break;
			}
		}
	}

	//disk1 checksum
	for (int i = 0; i < disk.size(); ++i) {
		if (disk[i] != -1) { 
			result1 += disk[i] * i; 
		}
	}

	//disk2 checksum
	for (int i = 0; i < disk2.size(); ++i) {
		if (disk2[i] != -1) {
			result2 += disk2[i] * i;
		}
	}

	std::cout << "9: " << result1 << " " << result2 << std::endl;
	return 1;
} 