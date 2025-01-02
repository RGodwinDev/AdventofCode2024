// AdventofCode2024.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "AdventofCode2024.h"

int main()
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    std::cout << "Advent of code 2024 :)" << std::endl;
    std::cout << "Check out rgodwin.dev" << std::endl;
    std::vector<Day*> Days;

    Days.push_back(new Day1()); //a simple 2 pointer loop
    Days.push_back(new Day2()); //slope increase/decrease, with tolerance
    Days.push_back(new Day3()); //regex
    Days.push_back(new Day4()); //first grid, x-mas. part1 check all directions, part2 only diags
    Days.push_back(new Day5()); //bubble sort
    Days.push_back(new Day6()); //grid traversal, loop detection
    Days.push_back(new Day7()); //bool recursive x*y == goal || x+y == goal || x concat y == goal
    Days.push_back(new Day8()); //grid traversal, save locations in a set
    Days.push_back(new Day9()); //storage manipulation
    Days.push_back(new Day10()); //grid traversal, bfs
    Days.push_back(new Day11()); //part 1 describes a list, part 2 uses all your ram, so you change to a frequency map.
    Days.push_back(new Day12()); 
    Days.push_back(new Day13()); //uses eigen for linear system solve with matrices
    Days.push_back(new Day14()); //Treeeee
    Days.push_back(new Day15());
    Days.push_back(new Day16());
    Days.push_back(new Day17());
    Days.push_back(new Day18()); //day 18 being converted to djikstras
    Days.push_back(new Day19());
    Days.push_back(new Day20());
    Days.push_back(new Day21());
    Days.push_back(new Day22());
    Days.push_back(new Day23());
    Days.push_back(new Day24());
    Days.push_back(new Day25()); //brute force forloops
    std::cout << "Problem Results    Part1                Part2" << std::endl;

    auto totalstart = std::chrono::high_resolution_clock::now();
    std::vector<std::chrono::microseconds> times;

    for (Day* D : Days) {
        auto start = std::chrono::high_resolution_clock::now();
        D->run();
        auto finish = std::chrono::high_resolution_clock::now();
        times.push_back(std::chrono::duration_cast<std::chrono::microseconds>(finish - start));
    }
    auto totalfinish = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << "---------Times---------" << std::endl;
    std::cout << "This includes reading the input and running part 1 and part 2" << std::endl;
    std::cout << "10k us -> 10ms, 10mil us -> 10sec" << std::endl;
    std::cout << "anything under 400us is probably not actually doing anything" << std::endl;
    for (int i = 0; i < times.size(); ++i) {
        if (times[i].count() > 10000000) {
            SetConsoleTextAttribute(hConsole, 04);
            std::cout << "day " << std::setw(2) << i + 1 << ": " << std::setw(4) << times[i].count() / 1000000 << "seconds" << std::endl;
            SetConsoleTextAttribute(hConsole, 07);
        }
        else if (times[i].count() > 10000) {
            SetConsoleTextAttribute(hConsole, 06);
            std::cout << "day " << std::setw(2) << i + 1 << ": " << std::setw(4) << times[i].count() / 1000 << "ms" << std::endl;
            SetConsoleTextAttribute(hConsole, 07);
        }
        else {
            SetConsoleTextAttribute(hConsole, 02);
            std::cout << "day " << std::setw(2) << i + 1 << ": " << std::setw(4) << times[i].count() << "us" << std::endl;
            SetConsoleTextAttribute(hConsole, 07);
        }
    }

    std::cout << std::endl << "Total time: " << std::chrono::duration_cast<std::chrono::milliseconds>(totalfinish - totalstart).count() << "ms" << std::endl;
    system("pause");
    return 0;
}

