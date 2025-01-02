#include "Day12.h"

int Day12::run() {

	std::string text;
	std::ifstream file("./day12input.txt");

	int result1 = 0;
	int result2 = 0;
	std::vector<std::string> xmas;

	while (getline(file, text)) {
		xmas.push_back(text);
	}

	//map < char, vector >, type of crop
	//vector < pair >, regions of that crop
	//pair< int, set >, size of region, and region
	//set < pair >, single region of the crop
	//pair <int,int>, position of the crop in that region
	std::map<char, std::vector<Day12Region>> crops;

	for (int i = 0; i < xmas.size(); ++i) {
		for (int j = 0; j < xmas[i].size(); ++j) {
			if (crops.find(xmas[i][j]) == crops.end()) { //a new crop!
				std::vector<Day12Region> v;
				Day12Region r({i,j});
				r.insert({ i,j });
				v.push_back(r);
				crops[xmas[i][j]] = v;
			}
			else { //either find a region for the crop, or make a new region
				std::vector<Day12Region>* cropRegions = &crops[xmas[i][j]];

				int up = -1;
				int left = -1;

				if (i > 0) {//look up
					for (int k = 0; k < cropRegions->size(); ++k) {
						if (cropRegions->at(k).contains({ i - 1, j })) {
							up = k;
							break;
						}
					}
				}
				if (j > 0) {//look left
					for (int k = 0; k < cropRegions->size(); ++k) {
						if (cropRegions->at(k).contains({ i, j - 1 })) {
							left = k;
							break;
						}
					}
				}
				if (up >= 0 && left >= 0) { //found regions at both up and left

					//if topright doesnt exist, 2 sides go away
					bool toprightexist = cropRegions->at(up).contains({ i - 1, j + 1 });
					if (!toprightexist) {
						cropRegions->at(up).sides -= 2; 
					}

					if (up == left) { //same region, just add position to it.
						cropRegions->at(up).insert({ i,j });

					}
					else { //different regions, merge them!
						//puts the left region into the up region
						
						for (std::pair<int, int> pos : cropRegions->at(left).getPlots()) {
							cropRegions->at(up).insert(pos);
						}
						//perimeter is just the 2 regions perimeters added together
						cropRegions->at(up).perimeter += cropRegions->at(left).perimeter;
						cropRegions->at(up).sides += cropRegions->at(left).sides;
						cropRegions->at(up).insert({ i,j });
						//remove the left region
						cropRegions->erase(cropRegions->begin() + left);
					}

				}
				else if (up >= 0) {
					cropRegions->at(up).insert({ i,j });
					cropRegions->at(up).perimeter += 2;
					
					//if topright exist
					if (cropRegions->at(up).contains({ i - 1, j + 1 })) {
						cropRegions->at(up).sides += 2;
					}
					
					//if topleft exist
					if (cropRegions->at(up).contains({ i - 1, j - 1 })) {
						cropRegions->at(up).sides += 2;
					}
				}
				else if (left >= 0) {
					cropRegions->at(left).insert({ i,j });
					cropRegions->at(left).perimeter += 2;

					//we just care if topleft exists
					if (cropRegions->at(left).contains({ i - 1, j - 1 })) {
						cropRegions->at(left).sides += 2;
					}
				}
				else { //no regions connected, create a new region
					Day12Region newRegion({i,j});
					cropRegions->push_back(newRegion);
				}
			}
		}
	}
	for (auto crop : crops) {
		for (Day12Region region : crop.second) {
			result1 += region.perimeter * region.getArea();
			result2 += region.sides * region.getArea();
		}
	}
	std::cout << std::setw(4) << "12: " << std::setw(20) << result1 << " " << std::setw(20) << result2 << std::endl;
	return 1;
}