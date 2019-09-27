/*
 * File: program.cpp
 * Author: John Ed Quinn
*/

/* PREAMBLE */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
using namespace std;

/// Function: performPermutations
/// Description: Creates permutations of length of hops by jumping through the map
bool performPermutation(string & sub, map <char, string> m, char start, int hops) {

	/* Perform permutations */
	if (sub.length() == hops) {
		cout << sub << endl;
		return true;
	} else {
		sub.push_back(start);
		for (int i = 0; i < m[start].length(); i++) {
			char c = m[start][i];
			if (performPermutation(sub, m, c, hops)) break;
		}
		sub.pop_back();
	}
	return false;
}


/// Function: main
/// Description: Main driver
int main(int argc, char * argv []) {

	// Map to determine where I can go from a certain digit
	map <char, string> m = {
		{'0', "46"},
		{'1', "68"},
		{'2', "79"},
		{'3', "48"},
		{'4', "039"},
		{'5', ""},
		{'6', "017"},
		{'7', "26"},
		{'8', "13"},
		{'9', "24"}
	};

	int start, hops;
	unsigned int index = 0;
	while (cin >> start) {
		/* For formatting */
		cin >> hops;
		index++; if (index > 1) cout << endl;

		/* Perform permutation */
		string sub;
		int i = 0;
		performPermutation(sub, m, '0' + start, hops);
	}	
	return 0;
}

