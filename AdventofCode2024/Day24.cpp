#include "Day24.h"

int Day24::run() {
	long long result1 = 0;
	int result2 = 0;
	std::fstream f("day24input.txt");
	std::string s;
	std::map<std::string, int> m;
	while (getline(f, s)) {
		if (s.size() == 0) { break; }
		m[s.substr(0, 3)] = stoi(s.substr(4));
	}

	std::queue<std::string> q;
	while (getline(f, s)) {
		std::stringstream ss(s);
		std::string first;
		ss >> first;
		std::string operation;
		ss >> operation;
		std::string second;
		ss >> second;
		std::string arrow;
		ss >> arrow;
		std::string result;
		ss >> result;

		if (m.find(result) == m.end()) {
			if (m.find(first) == m.end() || m.find(second) == m.end()) {
				q.push(s);
				continue;
			}
			if (operation == "AND") {
				m[result] = m[first] == 1 && m[second] == 1;
			}
			else if (operation == "XOR") {
				m[result] = m[first] != m[second];
			}
			else if (operation == "OR") {
				m[result] = m[first] == 1 || m[second] == 1;
			}
		}
	}

	while (!q.empty()) {
		std::string s2 = q.front();
		q.pop();
		std::stringstream ss(s2);
		std::string first;
		ss >> first;
		std::string operation;
		ss >> operation;
		std::string second;
		ss >> second;
		std::string arrow;
		ss >> arrow;
		std::string result;
		ss >> result;

		if (m.find(result) == m.end()) {
			if (m.find(first) == m.end() || m.find(second) == m.end()) {
				q.push(s2);
				continue;
			}
			if (operation == "AND") {
				m[result] = m[first] == 1 && m[second] == 1;
			}
			else if (operation == "XOR") {
				m[result] = m[first] != m[second];
			}
			else if (operation == "OR") {
				m[result] = m[first] == 1 || m[second] == 1;
			}
		}
	}

	for (auto p : m) {
		if (p.first[0] == 'z') {
			int power = stoi(p.first.substr(1, 2));
			result1 += p.second * pow(2, power);
		}
	}

	std::cout << "24: " << result1 << " " << result2 << std::endl;
	return 1;
}
