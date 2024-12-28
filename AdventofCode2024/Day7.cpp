#include "Day7.h"

int Day7::run() {
	std::string text;
	std::ifstream file("./day7input.txt");

	long long result1 = 0;
	long long result2 = 0;

	std::regex pattern(R"(-?\d+)");
	while (getline(file, text)) {
		std::regex_token_iterator<std::string::iterator> rend;
		std::regex_token_iterator<std::string::iterator> matches(text.begin(), text.end(), pattern);
		long long target = stoll(*matches++);
		std::vector<long long> values;
		while (matches != rend) {
			values.push_back(stoll(*matches++));
		}
		if (calc(values, 1, target, values[0])) {
			result1 += target;
		}
		if (calc2(values, 1, target, values[0])) {
			result2 += target;
		}
	}

	
	std::cout << "7: " << result1 << " " << result2 << std::endl;
	return 1;
}

//part 1 calc
bool Day7::calc(std::vector<long long>& v, int pos, long long target, long long cur) {
	if (pos == v.size() - 1) {
		return cur * v[pos] == target
			|| cur + v[pos] == target;
	}
	return calc(v, pos + 1, target, (cur * v[pos]))
		|| calc(v, pos + 1, target, (cur + v[pos]));
}

//part 2 calc
bool Day7::calc2(std::vector<long long> &v, int pos, long long target, long long cur) {
	long long concat = cur;
	long long x = v[pos];
	int xsize = 0;
	while (x > 0) {
		xsize++;
		x /= 10;
	}

	concat *= pow(10, xsize);
	concat += v[pos];
	
	if (pos == v.size() - 1) {
		return cur * v[pos] == target
			|| cur + v[pos] == target
			|| concat == target;
	}
	return calc2(v, pos+1, target, (cur * v[pos]))
		|| calc2(v, pos+1, target, (cur + v[pos]))
		|| calc2(v, pos + 1, target, concat);
}