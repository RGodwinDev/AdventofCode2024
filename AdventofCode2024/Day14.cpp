#include "Day14.h"

int Day14::run() {

	std::string text;
	std::ifstream file("./day14input.txt");

	int result1 = 0;
	int result2 = 0;

	//p=69,11 v=-25,6
	//p is position
	//v is velocity
	std::regex pattern(R"(-?\d+)");
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> swarm;
	while (getline(file, text)) {
		std::pair<int, int> p;
		std::pair<int, int> v;
		std::regex_token_iterator<std::string::iterator> rend;
		std::regex_token_iterator<std::string::iterator> matches(text.begin(), text.end(), pattern);
		while (matches != rend) {
			p.first = stoi(*matches++);
			p.second = stoi(*matches++);
			v.first = stoi(*matches++);
			v.second = stoi(*matches++);
		}
		std::pair<std::pair<int, int>, std::pair<int, int>> bot = { p,v };
		swarm.push_back(bot);
	}

	int width = 101;
	int height = 103;


	for (int i = 0; i < 100; ++i) {
		//move the bots
		for (std::pair<std::pair<int, int>, std::pair<int, int>>& b : swarm) {
			move(b, &width, &height);
		}
	}

	//calculate safety score
	int quad1 = 0;
	int quad2 = 0;
	int quad3 = 0;
	int quad4 = 0;

	for (std::pair<std::pair<int, int>, std::pair<int, int>>& b : swarm) {
		//center isnt in any quadrant
		//101 wide, 103 tall, so 50th and 51st
		if (b.first.first == width / 2 || b.first.second == height / 2) {
			continue;
		}

		//because multiplication is commutative
		//it doesnt matter which quad is actually where.
		//just that the bots for each quad are counted together.
		if (b.first.first > width / 2) {
			if (b.first.second > height / 2) {
				quad1++;
			}
			else {
				quad2++;
			}
		}
		else {
			if (b.first.second > height / 2) {
				;
				quad3++;
			}
			else {
				quad4++;
			}
		}
	}
	result1 = quad1 * quad2 * quad3 * quad4;

	int passes = 100;
	//part 2
	bool broke = false;
	while (!broke) {
		passes++;
		std::vector<int> wide(101,0);
		std::vector<int> tall(103,0);
		for (std::pair<std::pair<int, int>, std::pair<int, int>>& b : swarm) {
			move(b, &width, &height);
			wide[b.first.first]++;
			tall[b.first.second]++;
		}
		int columns = 0;
		int rows = 0;
		for (int i : wide) {
			if (i > 15) {
				rows++;
			}
		}
		for (int i : tall) {
			if (i > 15) {
				columns++;
			}
		}
		if (rows >= 2 && columns >= 2) {
			//this is all for drawing the graph, unneeded for just the result
			/*
			std::vector<std::vector<int>> tree;
			for (int i = 0; i < 103; ++i) {
				tree.push_back(std::vector<int>(101,0));
			}
			for (std::pair<std::pair<int, int>, std::pair<int, int>>& b : swarm) {
				tree[b.first.second][b.first.first]++;
			}
			
			for (std::vector<int> v : tree) {
				for (int j : v) {
					std::cout << j;
				}
				std::cout << std::endl;
			}
			*/
			result2 = passes;

			broke = true;
			/*
			* if you don't get a tree the first iteration, remove 'broke = true' and use this to step thru.
			system("pause");
			*/
		}
	}

	std::cout << "14: " << result1 << " " << result2 << std::endl;
	return 1;
}


void Day14::move(std::pair<std::pair<int, int>, std::pair<int, int>> &bot, int* width, int* height) {
	bot.first.first += bot.second.first;
	bot.first.second += bot.second.second;
	if (bot.first.first < 0) {
		bot.first.first += *width;
	}
	bot.first.first %= *width;
	if (bot.first.second < 0) {
		bot.first.second += *height;
	}
	bot.first.second %= *height;
}