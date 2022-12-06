#include "aoc.hpp"
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm> // for transform
#include <numeric> // for accumulate
#include <tuple>
#include <string> //for substr
#include <ranges>

using namespace std;
namespace ranges = std::ranges;

using range_t = tuple<int, int>;
using pair_t = tuple<range_t, range_t>;
using input_t = list<pair_t>;

// Parse
input_t parseInput(ifstream& input) {
    input_t output = {};

    for(string line; getline(input, line); ) {
        string r1a, r1b, r2a, r2b;
        int pos;

        pos = line.find("-"); r1a = line.substr(0, pos); line.erase(0, pos+1);
        pos = line.find(","); r1b = line.substr(0, pos); line.erase(0, pos+1);
        pos = line.find("-"); r2a = line.substr(0, pos); line.erase(0, pos+1);
        r2b = line;

        range_t r1 (stoi(r1a),stoi(r1b));
        range_t r2 (stoi(r2a),stoi(r2b));
        pair_t pair(r1, r2);

        output.push_back(pair);
    }
    return output;
}


// helper function
bool rangeContained(pair_t pair) {
    range_t r1 = get<0>(pair);
    range_t r2 = get<1>(pair);
    bool r1cr2 = get<0>(r1) <= get<0>(r2) && get<1>(r1) >= get<1>(r2);
    bool r2cr1 = get<0>(r2) <= get<0>(r1) && get<1>(r2) >= get<1>(r1);

    return r1cr2 || r2cr1;
}

bool rangeOverlaps(pair_t pair) {
    range_t r1 = get<0>(pair);
    range_t r2 = get<1>(pair);
    //easiest to reason ranges NOT overlapping.

    bool r1StrictBeforeR2 = get<1>(r1) < get<0>(r2); //end of r1, before start of r2
    bool r2StrictbeforeR1 = get<1>(r2) < get<0>(r1); //end of r2, before start of r1

    return !(r1StrictBeforeR2 || r2StrictbeforeR1);
}


// Part 1 solution
int part1 (input_t& input) {
    list<bool> overlapping;
    ranges::transform(input.cbegin(), input.cend(), back_inserter(overlapping), &rangeContained);
    int total = accumulate(overlapping.cbegin(), overlapping.cend(), 0);
    return total;
}

// Part 2 solution
int part2 (input_t& input) {
    list<bool> overlapping;
    ranges::transform(input.cbegin(), input.cend(), back_inserter(overlapping), &rangeOverlaps);
    int total = accumulate(overlapping.cbegin(), overlapping.cend(), 0);
    return total;
}

// Main
int main(int argc, char* argv[]) {
    // will warn and exit if first arg is not a valid file
    ifstream input = aoc::getInputStream(argc, argv);

    // valid file found; now parse
    input_t parse = parseInput(input);

    // answers
    int answer1 = part1(parse);
    cout << endl << "answer1: " << answer1 << endl;

    int answer2 = part2(parse);
    cout << endl << "answer2: " << answer2 << endl;
}
