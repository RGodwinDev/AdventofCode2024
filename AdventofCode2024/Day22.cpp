#include "Day22.h"

int Day22::run() {
	unsigned long long result1 = 0;
	int result2 = 0;
	std::vector<unsigned long> monkeySecrets;
	std::fstream f("./day22input.txt");
	std::string s;

	//count how many bananas you'd win if you use a certain sequence
	std::map<std::vector<int>, int> bananas;
	std::unordered_map<std::string, int> bananas2;

	while (getline(f, s)) {
		monkeySecrets.push_back(stol(s));
	}
	//step 1, multiply by 64 then mix and prune
	//step 2, divide by 32, round down to nearest int, then mix and prune
	//step 3, multiply by 2048, mix and prune

	//mix = bitwise XOR the multiplied number with secret number
	//prune = %16777216
	for (int i = 0; i < monkeySecrets.size(); ++i) {
		std::set<std::vector<int>> sequences;
		std::unordered_set<std::string> sequences2;
		std::vector<int> sequence;
		std::vector<int> banan;
		
		//insert the first sequence value and banana value
		sequence.push_back(0);
		banan.push_back(monkeySecrets[i]%10);
		
		//insert the next 3 values
		for (int j = 0; j < 3; ++j) {
			monkeySecrets[i] = ((monkeySecrets[i] << 6) ^ monkeySecrets[i]) % 16777216;
			monkeySecrets[i] = ((monkeySecrets[i] >> 5) ^ monkeySecrets[i]) % 16777216;
			monkeySecrets[i] = ((monkeySecrets[i] << 11) ^ monkeySecrets[i]) % 16777216;
			banan.push_back(monkeySecrets[i] % 10);
			sequence.push_back(banan[banan.size() - 1] - banan[banan.size() - 2]);
		}

		//insert the final 1996 values
		for (long j = 3; j < 2000; ++j) {
			/*
			* shift << multiply, >> divide
			* mix	XOR(^) self
			* prune %16777216 (2^24)
			*/
			monkeySecrets[i] = ((monkeySecrets[i] << 6) ^ monkeySecrets[i]) % 16777216;
			monkeySecrets[i] = ((monkeySecrets[i] >> 5) ^ monkeySecrets[i]) % 16777216;
			monkeySecrets[i] = ((monkeySecrets[i] << 11) ^ monkeySecrets[i]) % 16777216;

			
			//add the last digit to banan values
			banan.push_back(monkeySecrets[i] % 10);

			//difference of last 2 values in banan
			sequence.push_back(banan[banan.size() - 1] - banan[banan.size() - 2]);

			//remove the front of the sequence
			//release mode slows significantly if you dont do this (90+ seconds vs 2.5 seconds)
			sequence.erase(sequence.begin());

			std::string seq;
			for (int i = 0 /*sequence.size() - 4*/; i < sequence.size(); ++i) {
				seq += std::to_string(sequence[i]);
			}
			
			//if the sequence has been seen before, we've got a highest value for it
			if (sequences.find(sequence) == sequences.end()) {
				//all bananas with this sequence get added together
				bananas[sequence] += banan[banan.size() - 1];
				//add this sequence to seen sequences.
				sequences.insert(sequence);
			}
			
			//we convert to string so we can insert into sequences2, which is an unordered_set
			//vector<int> can't be hashed, but a string can.
			if (sequences2.find(seq) == sequences2.end()) {
				//all bananas with this sequence get added together
				bananas2[seq] += banan[banan.size() - 1];
				//add this sequence to seen sequences.
				sequences2.insert(seq);
			}
		}
	}
	
	for (unsigned long secret : monkeySecrets) {
		result1 += secret;
	}

	for (auto p : bananas2) {
		result2 = std::max(p.second, result2);
	}
	std::cout << std::setw(4) << "22: " << std::setw(20) << result1 << " " << std::setw(20) << result2 << std::endl;
	return 1;
}