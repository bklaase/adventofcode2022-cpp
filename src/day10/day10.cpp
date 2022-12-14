#include "aoc.hpp"
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <list>
#include <ranges>

using namespace std;
namespace ranges = std::ranges;

struct instruction_t {
    string cmd;
    int param;
};

using cycle_t = uint;
using state_t = map<cycle_t, int>;
using input_t = list<instruction_t>;

// Parse
input_t parseInput(ifstream& input) {
    input_t output = {};

    for(string line; getline(input, line); ) {
        stringstream is(line);
        string command, param;
        is >> command; is >> param;
        instruction_t instr {command, param.empty() ? 0 : stoi(param)};
        output.push_back(instr);
    }
    return output;
}


// helper functions
vector<cycle_t> processInstructions(input_t& input) {
    vector<cycle_t> cycles = {1};
    int x = 1;
    for(auto instr : input) {
        if(instr.cmd == "noop") cycles.push_back(x);
        else if(instr.cmd == "addx") {
            // 2 cycles
            cycles.push_back(x);
            cycles.push_back(x);
            x += instr.param;
        }
    }
    return cycles;
}

// Part 1 solution
uint part1 (input_t& input) {
    auto cycles = processInstructions(input);

    // now find signal strengths
    int result = 0;
    for(uint pos = 20; pos < cycles.size(); pos+= 40) {
        result += pos*cycles[pos];
    }
    return result;
}

// Part 2 solution
string part2 (input_t& input) {
    auto cycles = processInstructions(input);
    string monitor = "";

    for(uint pos = 0; pos < 240; pos++) {
        uint spritePos = cycles[pos+1];
        uint rowPos = (pos % 40);

        if(rowPos == 0)
            monitor.push_back('\n');

        if(spritePos -1 <= rowPos && rowPos <= spritePos +1)
            monitor.push_back('#');
        else
            monitor.push_back('.');
    }

    return monitor;
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

    auto answer2 = part2(parse);
    cout << endl << "answer2: " << endl << answer2 << endl;
}
