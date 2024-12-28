#include "Day17.h"

int Day17::run() {
	std::fstream f("day17input.txt");
	std::string text;
	std::string result1 = "";
	std::string result2 = "";
	std::regex pattern(R"(\d+)");
	std::regex_token_iterator<std::string::iterator> rend;

	getline(f, text);
	std::regex_token_iterator<std::string::iterator> match1(text.begin(), text.end(), pattern);
	int RegA = stoi(*match1);

	getline(f, text);
	std::regex_token_iterator<std::string::iterator> match2(text.begin(), text.end(), pattern);
	int RegB = stoi(*match2);

	getline(f, text);
	std::regex_token_iterator<std::string::iterator> match3(text.begin(), text.end(), pattern);
	int RegC = stoi(*match3);

	getline(f, text); //empty line
	getline(f, text);
	std::regex_token_iterator<std::string::iterator> matches(text.begin(), text.end(), pattern);
	std::vector<int> program;
	while (matches != rend) {
		int x = stoi(*matches++);
		program.push_back(x);
	}

	//instruction pointer, position in the program
	//except for jumps, it increases by 2 after each instruction.
	int ip = 0;
	while (ip < program.size()) {
		//8 values, 0-7
		int opcode = program[ip];
		//0 RegA = RegA / pow(2,combo)
		//1 RegB = RegB ^ operand
		//2 RegB = Combo % 8
		//3 if RegA != 0, goto program step(operand)
		//4 RegB = RegB ^ RegC
		//5 output the combo
		//6 RegB = RegA / pow(2,combo)
		//7 RegC = RegA / pow(2,combo)

		int literalOperand = program[ip + 1];
		//combo operands:
		int comboOperand = literalOperand;
		if (literalOperand == 4) { comboOperand = RegA; }
		else if (literalOperand == 5) { comboOperand = RegB; }
		else if (literalOperand == 6) { comboOperand = RegC; }
		else if (literalOperand == 7) {
			std::cout << "invalid operand " << literalOperand << std::endl;
		}

		if (opcode == 0) {
			RegA = RegA / (int)pow(2, comboOperand);
		}
		else if (opcode == 1) {
			RegB = RegB ^ literalOperand;
		}
		else if (opcode == 2) {
			RegB = comboOperand % 8;
		}
		else if (opcode == 3) {
			if (RegA != 0) {
				//jump to the operand
				ip = literalOperand;
				continue;
			}
		}
		else if (opcode == 4) {
			RegB = RegB ^ RegC;
		}
		else if (opcode == 5) {
			result1 += std::to_string(comboOperand % 8);
			result1 += ',';
		}
		else if (opcode == 6) {
			RegB = RegA / (int)pow(2, comboOperand);
		}
		else if (opcode == 7) {
			RegC = RegA / (int)pow(2, comboOperand);
		}
		else {
			std::cout << "invalid opcode " << opcode << std::endl;
		}
		ip += 2;
	}
	//the program has ended

	std::cout << "17: " << result1 << " " << result2 << std::endl;
	return 1;
}