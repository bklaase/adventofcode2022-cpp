#include "aoc.hpp"
#include <iostream>
#include <fstream>
#include <list>
#include <string> //for substr
#include <set> //for substr
#include <ranges>

using namespace std;
namespace ranges = std::ranges;

using input_t = string;

// Parse
input_t parseInput(ifstream& input) {
    input_t output = "";

    for(string line; getline(input, line); ) {
        output += line;
    }
    return output;
}


// helper functions
uint findNextMarkerPos(input_t& buffer, uint markerSize) {
    uint pos = 1; // puzzle assumes 1-indexed sequence
    string previous = "";
    for(char current : buffer) {
        if(pos < markerSize) {
            previous.push_back(current); pos++; continue;
        } // after this we are processing positions of markerSize and heigher

        //check if current, or any char matches one of the others; 
        set<char> charSet(previous.cbegin(), previous.cend());
        charSet.insert(current);
        if(charSet.size() == markerSize) return pos; // we're done. reminder: pos is 1-indexed

        // else dump oldest char, and rotate current char in
        previous.erase(0,1); previous.push_back(current);
        pos++;
    }
    return 0; // no markers found!
}

// Part 1 solution
uint part1 (input_t& input) {
    uint markerPos = findNextMarkerPos(input, 4);
    return markerPos;
}

// Part 2 solution
uint part2 (input_t& input) {
    uint markerPos = findNextMarkerPos(input, 14);
    return markerPos;
}

// Main
int main(int argc, char* argv[]) {
    // will warn and exit if first arg is not a valid file
    ifstream input = aoc::getInputStream(argc, argv);

    // valid file found; now parse
    input_t parse = parseInput(input);

    // answers
    uint answer1 = part1(parse);
    cout << endl << "answer1: " << answer1 << endl;

    uint answer2 = part2(parse);
    cout << endl << "answer2: " << answer2 << endl;
}
