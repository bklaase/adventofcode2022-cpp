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

using item_t = char;
using compartment_t = string;
using rucksack_t = tuple<compartment_t, compartment_t>;
using input_t = list<rucksack_t>;
using group_t = tuple<string, string, string>;

// Parse
input_t parseInput(ifstream& input) {
    input_t output = {};

    for(string line; getline(input, line); ) {
        int noItems = line.size();
        compartment_t comp1 = line.substr(0, (noItems / 2));
        compartment_t comp2 = line.substr(noItems / 2, noItems / 2 );

        rucksack_t current(comp1,comp2);
        output.push_back(current);
    }
    return output;
}

list<group_t> parseInput2(ifstream& input) {
    list<group_t> output = {};

    for(string line; getline(input, line); ) {
        // each loop take three and create 3-tuple
        string line2, line3;
        getline(input, line2);
        getline(input, line3);

        group_t group(line, line2, line3);

        output.push_back(group);
    }
    return output;
}


// helper functions
int getItemPriority(item_t item) {
    if (97 <= item && item <= 122) // a-z have prio 1-26 and are ascii codes 97-122
        return item - 96;
    if(65 <= item && item <= 90) // A-Z have prio 27-52 and are ascii codes 65-90
        return item - 38;
    else {
        cout << "invalid item to get prio of: '" << item << "'\n";
        exit(1);
    }
}

item_t findDuplicate(rucksack_t rucksack) {
    string comp1 = get<0>(rucksack);
    string comp2 = get<1>(rucksack);
    ranges::sort(comp1);
    ranges::sort(comp2);

    //in theory every combi has exactly ONE duplicate item. so basic set intersec should find it:
    string difference;

    ranges::set_intersection(comp1, comp2, back_inserter(difference));

    return difference[0];
}

item_t findDuplicate2(group_t group) {
    string rucksack1 = get<0>(group);
    string rucksack2 = get<1>(group);
    string rucksack3 = get<2>(group);
    ranges::sort(rucksack1);
    ranges::sort(rucksack2);
    ranges::sort(rucksack3);

    string inter12;
    string inter123;

    ranges::set_intersection(rucksack1,rucksack2, back_inserter(inter12));
    ranges::set_intersection(inter12, rucksack3, back_inserter(inter123));

    return inter123[0];
}


// Part 1 solution
int part1 (input_t& input) {
    // get list of all duplicates
    list<item_t> dupes;
    list<int> totals;
    ranges::transform(input, back_inserter(dupes), &findDuplicate);
    ranges::transform(dupes, back_inserter(totals), &getItemPriority);

    int totalPrio = accumulate(totals.cbegin(), totals.cend(), 0);
    return totalPrio;
}

// Part 2 solution
int part2 (list<group_t>& input) {
    list<item_t> dupes;
    list<int> totals;

    ranges::transform(input, back_inserter(dupes), &findDuplicate2);
    ranges::transform(dupes, back_inserter(totals), &getItemPriority);
    int totalPrio = accumulate(totals.cbegin(), totals.cend(), 0);

    return totalPrio;
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

    input = aoc::getInputStream(argc, argv);
    list<group_t> parse2 = parseInput2(input);
    int answer2 = part2(parse2);
    cout << endl << "answer2: " << answer2 << endl;
}
