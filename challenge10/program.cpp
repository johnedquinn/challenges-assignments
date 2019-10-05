/*
 * File: program.cpp
 * Author: John Ed Quinn
*/

/* PREAMBLE */
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_set>
#include <bitset>
using namespace std;

/// Function: performPermutations
/// Description: Performs the permutations
bool performPermutations(unordered_set <bitset<16>> & s, bitset <16> & set, int k, int start, int n) {
	if (set.count() == k && s.find(set) == s.end()) {
		s.insert(set);
		for (int i = 0; i < n; i++) cout << set[i];
		cout << endl;
		return true;
	}
	for (int i = start; i < n; i++) {
		set &= ~(1<<i);
		if (performPermutations(s, set, k, i + 1, n)) break;
	}
	for (int i = start; i < n; i++) {
		set |= (1<<i);
		if (performPermutations(s, set, k, i + 1, n)) break;
	}
	return false;
}

/// Function: getInput
/// Description: get input from user
bool getInput(int & n, int & k) {
	string input;
	if (getline(cin, input)) {
		stringstream ss(input);
		ss >> n;
		ss >> k;
		return true;
	}
	return false;
}

/// Function: main
/// Description: X
int main(int argc, char * argv []) {
	int n, k;
	bool firstRound = true;
	while (getInput(n, k)) {
		if (!firstRound) cout << endl;
		firstRound = false;
		bitset <16> set;
		unordered_set <bitset <16>> s;
		performPermutations(s, set, k, 0, n);
	}

	return 0;
}

