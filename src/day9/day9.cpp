#include "aoc.hpp"
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <string> //for substr
#include <sstream>
#include <set>
#include <vector>
#include <ranges>

using namespace std;
namespace ranges = std::ranges;

struct instruction_t {
    string direction;
    int steps;
};
struct position_t { 
    int x = 0;
    int y = 0;
    auto operator<=>(const position_t&) const = default;
};

using field_t = map<position_t, int>;
using input_t = list<instruction_t>;

// Parse
input_t parseInput(ifstream& input) {
    input_t output = {};

    for(string line; getline(input, line); ) {
        stringstream is(line);
        string direction, steps;
        is >> direction; is >> steps;
        instruction_t instr {direction, stoi(steps)};
        output.push_back(instr);
    }
    return output;
}


// helper functions
void updateHeadPos(position_t& start, instruction_t instr) {
    int dirX=0, dirY=0;
    if(instr.direction == "U")
        dirY=1;
    if(instr.direction == "D")
        dirY=-1;
    if(instr.direction == "L")
        dirX=-1;
    if(instr.direction == "R")
        dirX=1;

    start.x += dirX;
    start.y += dirY;
}

void updateTailPos(position_t& posH, position_t& posT)
{
    auto comp = [](int a, int b) {return a < b ? -1 : (a == b ? 0 : 1); };
    int dirX=0, dirY=0;
    if(posH.y > posT.y+1)
        { dirY=1; dirX=comp(posH.x,posT.x); }
    else if(posH.y < posT.y-1)
        { dirY=-1; dirX=comp(posH.x,posT.x); }
    else if(posH.x < posT.x-1)
        { dirX=-1; dirY=comp(posH.y,posT.y); }
    else if(posH.x > posT.x+1)
        { dirX=1; dirY=comp(posH.y,posT.y); }


    posT.x += dirX;
    posT.y += dirY;
}

// Part 1 solution
uint part1 (input_t& input) {
    field_t field;
    position_t posH {0,0};
    position_t posT {0,0};
    for (auto instr : input) {
        for( int step = 0; step < instr.steps; step++) {
            updateHeadPos(posH, instr);
            updateTailPos(posH, posT);
            if(field.contains(posT))
                field[posT] += 1;
            else
                field[posT] = 1;
        }

    }
    return field.size();

}

// Part 2 solution
uint part2 (input_t& input) {
    field_t field;
    position_t posH,pos1,pos2,pos3,pos4,pos5,pos6,pos7,pos8,pos9;
    for (auto instr : input) {
        for( int step = 0; step < instr.steps; step++) {
            updateHeadPos(posH, instr);
            updateTailPos(posH, pos1);
            updateTailPos(pos1, pos2);
            updateTailPos(pos2, pos3);
            updateTailPos(pos3, pos4);
            updateTailPos(pos4, pos5);
            updateTailPos(pos5, pos6);
            updateTailPos(pos6, pos7);
            updateTailPos(pos7, pos8);
            updateTailPos(pos8, pos9);
            if(field.contains(pos9))
                field[pos9] += 1;
            else
                field[pos9] = 1;
        }
    }
    return field.size();
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
