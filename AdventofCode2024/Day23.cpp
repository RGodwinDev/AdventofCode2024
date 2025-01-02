#include "Day23.h"

int Day23::run() {

	int result1 = 0;
	int result2 = 0;
	//example line: ta-ab
	//represents 2 nodes and their link
	//link is both ways (nondirectional)
	//just make an undirected graph
	//we must find triples, same values != same vert

	std::fstream f("day23input.txt");
	std::string s;
	std::vector<std::pair<std::string, std::string>> connections;
	while (getline(f, s)) {
		std::string a = s.substr(0, 2);
		std::string b = s.substr(3);
		connections.push_back( {a, b} );
	}

	std::sort(connections.begin(), connections.end());
	std::vector<int> tripleIndexes;
	//a triple must have a-b, b-c, c-a
	//if we have an a-b, and a-c, look for b-c
	for (int i = 0; i < connections.size(); ++i) {
		//check tripleIndexes for i
		if (std::binary_search(tripleIndexes.begin(), tripleIndexes.end(), i)) { continue; }

		std::pair<std::string, std::string> a = connections[i];
		for (int j = 0; j < connections.size(); ++j) {
			if (j == i) { continue; }
			
			//check tripleIndexes for j
			if (std::binary_search(tripleIndexes.begin(), tripleIndexes.end(), j)) { continue; }

			std::pair<std::string, std::string> b = connections[j];
			std::pair<std::string, std::string> c = { "0","0" };
			if (b.first == a.first) {
				c = { b.second, a.second };
			}
			else if (b.first == a.second) {
				c = { b.second, a.first };
			}
			else if (b.second == a.first) {
				c = { b.first, a.second };
			}
			else if (b.second == a.second) {
				c = { b.first, a.first };
			}

			if (c.first != "0" && c.second != "0") {
				//search for the missing piece
				//binary search, cause we sorted them earlier
				
				//these are for lookin up the reverse later
				std::pair<std::string, std::string> d = { a.second, a.first };
				std::pair<std::string, std::string> e = { b.second, b.first };
				std::pair<std::string, std::string> f = { c.second, c.first };
				if (std::binary_search(connections.begin(), connections.end(), c)) {
					int place = std::lower_bound(connections.begin(), connections.end(), c) - connections.begin();
					tripleIndexes.push_back(i);
					tripleIndexes.push_back(j);
					tripleIndexes.push_back(place);

					if (std::binary_search(connections.begin(), connections.end(), d)) {
						int dplace = std::lower_bound(connections.begin(), connections.end(), d) - connections.begin();
						tripleIndexes.push_back(dplace);
					}
					if (std::binary_search(connections.begin(), connections.end(), e)) {
						int dplace = std::lower_bound(connections.begin(), connections.end(), e) - connections.begin();
						tripleIndexes.push_back(dplace);
					}
					if (std::binary_search(connections.begin(), connections.end(), f)) {
						int dplace = std::lower_bound(connections.begin(), connections.end(), f) - connections.begin();
						tripleIndexes.push_back(dplace);
					}

					if (a.first[0] == 't' || a.second[0] == 't' ||
						b.first[0] == 't' || b.second[0] == 't' ||
						c.first[0] == 't' || c.second[0] == 't') {
						result1++;
					}
					std::sort(tripleIndexes.begin(), tripleIndexes.end());
				}
				else if(std::binary_search(connections.begin(), connections.end(), d)){
					int place = std::lower_bound(connections.begin(), connections.end(), d) - connections.begin();
					tripleIndexes.push_back(i);
					tripleIndexes.push_back(j);
					tripleIndexes.push_back(place);
					if (std::binary_search(connections.begin(), connections.end(), e)) {
						int dplace = std::lower_bound(connections.begin(), connections.end(), e) - connections.begin();
						tripleIndexes.push_back(dplace);
					}
					if (std::binary_search(connections.begin(), connections.end(), f)) {
						int dplace = std::lower_bound(connections.begin(), connections.end(), f) - connections.begin();
						tripleIndexes.push_back(dplace);
					}
					if (a.first[0] == 't' || a.second[0] == 't' ||
						b.first[0] == 't' || b.second[0] == 't' ||
						c.first[0] == 't' || c.second[0] == 't') {
						result1++;
					}
					std::sort(tripleIndexes.begin(), tripleIndexes.end());
				}
			}
		}
	}
	
	std::cout << std::setw(4) << "23: " << std::setw(20) << result1 << " " << std::setw(20) << result2 << std::endl;
	return 1;
}