#include "aoc.hpp"
#include <iostream>
#include <fstream>
#include <list>
#include <string> //for substr
#include <sstream>
#include <set>
#include <ranges>
#include <map>

using namespace std;
namespace ranges = std::ranges;

struct file_t {
    string name;
    uint size;
};

struct folder_t {
    string name;
    uint size;
    string parentFolder;
    list<file_t> files;
};


using input_t = map<string, folder_t>;

// Parse
input_t parseInput(ifstream& input) {
    folder_t root {"/", 0, "",{}};
    string cwd = "/";
    map<string, folder_t> folders;
    folders[cwd] = root;

    for(string line; getline(input, line); ) {
        stringstream ls(line);
        string w1, w2, w3;
        ls >> w1; ls >> w2; ls >> w3; //max 3 words per line

        // ignores
        if(w1 == "$" && w2 == "ls") continue; // ignore
        if(w1 == "dir") continue; // ignore

        // $ cd
        if(w1 == "$" && w2 == "cd" ) {
            if(w3 == "/") continue; // skip 'cd /'

            // $ cd ..
            if(w3 == "..") {
                folders[folders[cwd].parentFolder].size += folders[cwd].size;
                cwd = folders[cwd].parentFolder;
                continue;
            }
            // $ cd <foldername>
            string newPath = cwd+"/"+w3;
            folder_t newCurrent {newPath, 0, cwd,{}};
            cwd = newPath;
            folders[cwd] = newCurrent;
        }
        else {
            // and so we are left with <size> <filename> entries
            uint size = stoi(w1);
            file_t newFile {w2, size};
            folders[cwd].files.push_back(newFile);
            folders[cwd].size += size;
        }
    }
    while (folders[cwd].name != "/") {
        // treat as cd ..
        folders[folders[cwd].parentFolder].size += folders[cwd].size;
        cwd = folders[cwd].parentFolder;
    }

    return folders;
}


// Part 1 solution
uint part1 (input_t& input) {
    int totalSize;
    for(auto [key,val] : input) {
        if(val.size < 100000) totalSize += val.size;
    }

    return totalSize;
}

// Part 2 solution
uint part2 (input_t& input) {
    uint spaceUsed = input["/"].size;
    uint diskSize = 70000000;
    uint spaceRequired = 30000000 - (diskSize - spaceUsed);
    set<uint> orderedDirSizes;

    for(auto [key,val] : input) {
        if(val.size >= spaceRequired) {
            orderedDirSizes.insert(val.size);
        }
    }
    return *orderedDirSizes.begin();

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
