#include "Day3.h"

int Day3::run() {
	std::string text;
	std::ifstream file("./day3input.txt");

	//gets results that match "do()", "don't()", or "mul(###,###)"
	//std::regex pattern("do\\(\\)|don't\\(\\)|mul\\(\\d{1,3},\\d{1,3}\\)");

	//stole this from TheSilverDragoness, improved the time to ~55ms from >250ms
	std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
	

	int result1 = 0;
	int result2 = 0;
	std::string s = "";
	while (getline(file, text)) {
		s.append(text);
	}

	//this method also works, but is still running >250ms
	bool enabled = true;
	std::regex_token_iterator<std::string::iterator> rend;

	std::regex_token_iterator<std::string::iterator> matches(s.begin(), s.end(), pattern);
	while (matches != rend) {
		std::string match = *matches++;
		//std::cout << match << std::endl;
		if (match == "do()") { enabled = true; }
		else if (match == "don't()") { enabled = false; }
		else {
			//mul(###,###)
			int x = stoi(match.substr(4));
			/*
			int xsize = 0;
			int xtemp = x;
			while (xtemp > 0) {
				xsize++;
				xtemp /= 10;
			}
			*/
			//didnt change total time much.
			int xsize = ceil(log10(x));

			int y = stoi(match.substr(5 + xsize));

			result1 += x * y;
			if (enabled) {
				result2 += x * y;
			}
		}
	}

	/*
	* this works, but ran >250ms
	//search the string for matching patterns
	bool enabled = true;
	std::string::const_iterator searchStart = s.begin();
	for (std::smatch m; std::regex_search(searchStart, s.cend(), m, pattern);) {
		std::string mstring = m.str();
		//std::cout << mstring << std::endl;
		if (		mstring == "do()") {	enabled = true; }
		else if (	mstring == "don't()") {	enabled = false; }
		else {
			//get a
			int a = stoi(mstring.substr(4));

			//get the size of a
			int asize = 0;
			int atemp = a;
			while (atemp > 0) {
				asize++;
				atemp /= 10;
			}

			//get b
			int b = stoi(mstring.substr(5 + asize));

			//result1 is always on
			result1 += a * b;
			//result2 depends on if mul is enabled or not
			if (enabled) {
				result2 += a * b;
			}
		}
		searchStart = m.suffix().first;
	}
	*/


	std::cout << "3: " << result1 << " " << result2 << std::endl;
	return 1;
}