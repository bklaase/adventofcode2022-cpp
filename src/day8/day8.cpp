#include "aoc.hpp"
#include <iostream>
#include <fstream>
#include <list>
#include <string> //for substr
#include <set>
#include <vector>
#include <ranges>

using namespace std;
namespace ranges = std::ranges;

using treeRow_t = vector<int>;
using input_t = vector<treeRow_t>;

// Parse
input_t parseInput(ifstream& input) {
    input_t output = {};

    for(string line; getline(input, line); ) {
        treeRow_t line_vector = {};
        for(auto c : line) {
            line_vector.push_back(atoi(&c));
        }
        output.push_back(line_vector);
    }
    return output;
}


// helper functions
bool isTreeVisible(int x, int y, input_t& trees) {
    // horizontal movement is easy:
    // from 0,y -> x-1,y
    set<int> treesToLeft(trees[y].cbegin(), trees[y].cbegin() + x);
    // from x+1,y -> maxX,y
    set<int> treesToRight(trees[y].cbegin()+(x+1), trees[y].cend());
    // tree is visible from the left, OR the right, if there are no trees in these sets, with greater or equal height

    auto seenFromSet = [&](set<int> treesToEdge) {
        return treesToEdge.empty() || *treesToEdge.rbegin() < trees[y][x];
    };

    bool seenFromLeft = seenFromSet(treesToLeft);
    bool seenFromRight = seenFromSet(treesToRight);
    if(seenFromLeft || seenFromRight)
        return true;

    // traversing vertically is similar, though a bit more annoying
    set<int> treesToTop;
    set<int> treesToBottom;
    for_each(trees.cbegin(), trees.cbegin() + y, [&](auto treeLine) {treesToTop.insert(treeLine[x]);});
    for_each(trees.cbegin() + (y+1), trees.cend(), [&](auto treeLine) {treesToBottom.insert(treeLine[x]);});

    bool seenFromTop = seenFromSet(treesToTop);
    bool seenFromBottom = seenFromSet(treesToBottom);
    if (seenFromTop || seenFromBottom)
        return true;

    return false;
}

int treeScenicScore(int x, int y, input_t& trees) {
    // in four directions, until edge, or equal+ tree.
    int maxX = trees[0].size();
    int maxY = trees.size();

    int upScore = 0;
    for(int i=y-1; i >= 0; i--) {
        upScore ++;
        if(trees[i][x] >= trees[y][x]) break;
    }
    int downScore = 0;
    for(int i=y+1; i < maxY; i++) {
        downScore ++;
        if(trees[i][x] >= trees[y][x]) break;
    }
    int leftScore = 0;
    for(int i=x-1; i >= 0; i--) {
        leftScore ++;
        if(trees[y][i] >= trees[y][x]) break;
    }
    int rightScore = 0;
    for(int i=x+1; i < maxX; i++) {
        rightScore ++;
        if(trees[y][i] >= trees[y][x]) break;
    }
    return upScore * downScore * leftScore * rightScore;
}

// Part 1 solution
uint part1 (input_t& input) {
    int maxX = input[0].size();
    int maxY = input.size();

    int treesVisible = 0;

    for(int x = 0; x < maxX; x++) {
        for (int y = 0; y < maxY; y++) {
            if(isTreeVisible(x, y, input))
                treesVisible++;
        }
    }

    return treesVisible;
}

// Part 2 solution
uint part2 (input_t& input) {
    int maxX = input[0].size();
    int maxY = input.size();

    int maxScenicScore = 0;

    for(int x = 0; x < maxX; x++) {
        for (int y = 0; y < maxY; y++) {
            int score = treeScenicScore(x,y,input);
            if(score > maxScenicScore)
                maxScenicScore = score;
        }
    }
    return maxScenicScore;
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
