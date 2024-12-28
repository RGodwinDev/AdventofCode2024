#include "Day11.h"

int Day11::run() {
	std::string text;
	std::ifstream file("./day11input.txt");

	long long result1 = 0;
	long long result2 = 0;
	std::vector<std::string> xmas;

	while (getline(file, text)) {
		xmas.push_back(text);
	}
	
	//Day11List list = *new Day11List();
	std::stringstream ss(xmas[0]);
	std::string s;

	/*
	* BRUTE FORCE -> part 2 needs several terabites to store the list, lol.
	*
	Day11ListNode* prev = nullptr;
	while (getline(ss, s, ' ')) {
		if (prev) {
			prev->next = new Day11ListNode(std::stoll(s));
			prev = prev->next;
		}
		else {
			list.head = new Day11ListNode(std::stoll(s));
			prev = list.head;
		}
		list.size++;
	}
	
	//25 blinks
	//i expect part 2 to do a big number, making this unfeasable without a better strat.
	for (int i = 0; i < 75; ++i) {
		std::cout << "blink: " << i << std::endl;
		Day11ListNode* cur = list.head;
		while (cur) {
			if (cur->val == 0) {
				cur->val = 1;
				cur = cur->next;
				continue;
			}
			//get size of val
			long long x = cur->val;
			int xsize = 0;
			while (x > 0) {
				xsize++;
				x /= 10;
			}
			if (xsize % 2 == 0) { //even size
				//split the number, create a new stone
				//x % 10^(xsize/2)?

				//std::cout << cur->val << " " << xsize / 2 << std::endl;
				//std::cout << cur->val % (long long)std::pow(10, xsize / 2) << std::endl;
				//right half
				Day11ListNode* n = new Day11ListNode(cur->val % (long long)std::pow(10, xsize / 2));
				//cur keeps left half
				cur->val = cur->val / pow(10, xsize / 2);
				//insert n inbetween cur and cur->next
				n->next = cur->next;
				cur->next = n;
				list.size++;
				cur = cur->next->next;
			}
			else {
				cur->val = cur->val * 2024;
				cur = cur->next;
			}
		}
	}
	result1 = list.size;
	*/
	std::map<long long, long long> m;

	while (getline(ss, s, ' ')) {
		m[stoll(s)]++;
	}

	//blink 25 times for part 1
	blink(&m, 25);
	for (auto n : m) {
		result1 += n.second;
	}

	//blink another 50 times for part 2
	blink(&m, 50);
	for (auto n : m) {
		result2 += n.second;
	}

	std::cout << "11: " << result1 << " " << result2 << std::endl;
	return 1;
}


//blinks 'blinks' times for the stones in m.
void Day11::blink(std::map<long long,long long> *m, int blinks) {
	for (int i = 0; i < blinks; ++i) {
		std::map<long long, long long> freq;
		for (std::pair<long long, long long> n : *m) {
			if (n.first == 0) {
				freq[1] += n.second;
				continue;
			}
			long long x = n.first;
			int xsize = 0;
			while (x > 0) {
				xsize++;
				x /= 10;
			}
			if (xsize % 2 == 0) { //even size
				//right half
				freq[n.first % (long long)std::pow(10, xsize / 2)] += n.second;
				//left half
				freq[n.first / (long long)std::pow(10, xsize / 2)] += n.second;
			}
			else {
				freq[n.first * 2024] += n.second;
			}
		}
		*m = freq;
	}
}