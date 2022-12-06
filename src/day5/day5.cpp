#include "aoc.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <list>
#include <ranges>

using namespace std;
namespace ranges = std::ranges;

using stacks_t = vector<string>;
struct moveInstruction {
    uint from;
    uint amount;
    uint to;
};

struct cargoState {
    list<moveInstruction> instructions;
    stacks_t stacks;

};

using input_t = cargoState;


// Parse
// as of this time no parsing of the starting state .. :), Maybe later
input_t parseInput(ifstream& input) {
    input_t output;
    // stacks_t stacks = {"ZN", "MCD", "P"}; //example input
    stacks_t stacks = {"BSVZGPW","JVBCZF","VLMHNZDC","LDMZPFJB","VFCGJBQH","GFQTSLB","LGCZV","NLG","JFHC"}; //real input
    list<moveInstruction> instructions = {};

    for(string line; getline(input, line); ) {
        stringstream ls(line);
        moveInstruction mi;
        string none, amount, from, to;

        ls >> none; ls >> amount; mi.amount = stoi(amount);
        ls >> none; ls >> from; mi.from = stoi(from);
        ls >> none; ls >> to; mi.to = stoi(to);

        instructions.push_back(mi);
    }

    output.instructions = instructions;
    output.stacks = stacks;
    return output;
}


// helper functions
void applyInstruction(stacks_t& stacks, moveInstruction& instruction, bool preserveOrder=false) {
    uint amount = instruction.amount;
    uint from = instruction.from -1;
    uint to = instruction.to -1;
    string cratesToMove = "";

    for(uint i = 1; i <= amount; i++) {
        cratesToMove.push_back(stacks[from].back());
        stacks[from].pop_back();
    }
    if (preserveOrder)
        ranges::reverse(cratesToMove);
    stacks[to] += cratesToMove;
}

string getMessageFromStacks(stacks_t& stacks) {
    string message = "";
    for(auto stack : stacks)
        message.push_back(stack.back());
    return message;
}

// Part 1 solution
string part1 (input_t& input) {
    for(auto instruction : input.instructions)
        applyInstruction(input.stacks, instruction);

    string message = getMessageFromStacks(input.stacks);

    return message;
}

// Part 2 solution
string part2 (input_t& input) {
    for(auto instruction : input.instructions)
        applyInstruction(input.stacks, instruction, true);

    string message = getMessageFromStacks(input.stacks);

    return message;
}

// Main
int main(int argc, char* argv[]) {
    // will warn and exit if first arg is not a valid file
    ifstream input = aoc::getInputStream(argc, argv);

    // valid file found; now parse
    input_t parse = parseInput(input);

    // answers
    auto answer1 = part1(parse);
    cout << endl << "answer1: " << answer1 << endl;

    // lazy, but these parts are destructive on input. reparse
    input = aoc::getInputStream(argc, argv);
    parse = parseInput(input);
    auto answer2 = part2(parse);
    cout << endl << "answer2: " << answer2 << endl;
}
