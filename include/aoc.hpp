#include <iostream>
#include <fstream>

using namespace std;

namespace aoc {
	ifstream getInputStream(int argc, char *argv[])
	{

		// check if input file arg is given
		if(argc < 1) {
			cout << "please supply input file\n\n";
			exit(1);
		}

		// try read input file from cli arg 1
		ifstream input (argv[1]);

		if (!input.is_open()) {
			cout << "Error opening file: " << argv[1];
			exit(1);
		}

		return input;
	}
}
