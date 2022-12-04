#include "aoc.hpp"
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <numeric>

using namespace std;

typedef list<int> backpack_t;
typedef list<backpack_t> input_t;

// Parse
input_t parseInput(ifstream & input) {
	string line;
	input_t output = {};
	backpack_t current = {};


	for(string line; getline(input, line); ) {
		if(line.empty()) {
			output.push_back(current);
			current = {};
		}
		else
			current.push_back(stoi(line));
	}
	output.push_back(current);
	return output;
}

// helper function: get totals from int list list
list<int> getTotals (input_t &input) {
	// replace all groups of ints, with their sum
	list<int> totals(input.size(),0);
	transform(input.cbegin(), input.cend(), totals.begin(),
			  [](backpack_t part) {
				  return accumulate(part.cbegin(), part.cend(), 0);
			  });

	return totals;
}

// Part 1 solution
int part1 (input_t &input) {
	auto totals = getTotals(input);

	// sort totals list and return heighest nr
	totals.sort();
	return totals.back();
}

// Part 2 solution
int part2 (input_t &input) {
	auto totals = getTotals(input);

	// sort totals list and return heighest 3 nrs
	totals.sort();
	int result = 0;
	for(int i = 0; i < 3; i++) {
		result += totals.back();
		totals.pop_back();
	}
	return result;
}

// Main
int main(int argc, char *argv[]) {

	// will warn and exit if first arg is not a valid file
	ifstream input = aoc::getInputStream(argc, argv);

	// valid file found; now parse
	auto parse = parseInput(input);

	// answers
	int answer1 = part1(parse);
	cout << endl << "answer1: " << answer1 << endl;

	int answer2 = part2(parse);
	cout << endl << "answer2: " << answer2 << endl;
}
