#include "aoc.hpp"
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include <numeric>
#include <tuple>

using namespace std;

typedef tuple<char,char> round_t;
typedef list<round_t> input_t;

// Parse
input_t parseInput(ifstream& input) {
    string line;
    input_t output = {};

    for(string line; getline(input, line); ) {
        round_t current (line[0],line[2]);
        output.push_back(current);
    }
    return output;
}

// helper functions
int scoreRound (round_t round) {
    int score = 0;
    char their = get<0>(round);
    char mine = get<1>(round);

    // score based on starting Value
    if (mine == 'X')
        score += 1;
    else if (mine == 'Y')
        score += 2;
    else if (mine == 'Z')
        score += 3;

    // score based on match result
    int result = mine - their;
    if (result == 23) // draw
        score += 3;
    if (result == 24 || result == 21) // win
        score += 6;
    return score;
}

round_t fixRound(round_t round) {
    char their = get<0>(round);
    char outcome = get<1>(round);

    round_t newRound;
    int offset;

    // score based on outcome
    if (outcome == 'Y') // draw
        offset = 23;

    else if (outcome == 'Z') {// win
        offset = 24;
        if (their == 'C')
            offset = 21;
    }

    else if (outcome == 'X') { // lose
        offset = 22;
        if (their == 'A')
            offset = 25;
    }

    newRound = make_tuple(their, their+offset);
    return newRound;
}

// Part 1 solution
int part1 (input_t& input) {
    // calculate scores
    list<int> totals(input.size(), 0);
    transform(input.cbegin(), input.cend(),
              totals.begin(), &scoreRound);

    // sum
    int sum = accumulate(totals.cbegin(), totals.cend(), 0);
    return sum;
}

// Part 2 solution
int part2 (input_t& input) {
    // fix input given new interpretation
    transform(input.cbegin(), input.cend(),
              input.begin(), &fixRound); // in place

    // calculate scores
    return part1(input);
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
