#include "Day1.h"

int Day1::run() {
	int result1 = 0;
	int result2 = 0;
	std::string text;
	std::fstream file("./day1input.txt");
	
	std::vector<int> left;
	std::vector<int> right;
	
	while (getline(file, text)) {
		left.push_back(stoi(text.substr(0, 6)));
		right.push_back(stoi(text.substr(6)));
	}

	//if we binary insertion sorted, we could take this out, would be 1 less O(n)
	std::sort(left.begin(), left.end()); 
	std::sort(right.begin(), right.end());

	//distance of left and right in each list
	for (int i = 0; i < left.size(); ++i) {
		result1 += abs(right[i] - left[i]);
	}

	//part 2
	//similarity score = add up number in left list after multiplying it by number of times it's in right list.
	//could do a 2 pointers, since we know the lists are sorted.
	int l = 0;
	int r = 0;
	while (l < left.size() && r < right.size()) {
		if (left[l] == right[r]) { 
			result2 += left[l]; r++;
		}
		else if (left[l] < right[r]) { l++; }
		else { r++; } //left is bigger
	}

	std::cout << std::setw(4) << "1: " << std::setw(20) << result1 << " " << std::setw(20) << result2 << std::endl;
	return 1;
}