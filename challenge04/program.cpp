/*
 * File: challenge04/program.cpp
 * Author: John E Quinn
*/

/* Preamble */
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

/// Function: read_numbers
/// Description: Reads in lines of numbers and appends them to vector
bool read_numbers(vector <int> & numbers) {
	numbers.clear();
	string line;
	if (getline(cin, line)) {
		stringstream ss(line);
		int n;
		while (ss >> n) {
			numbers.push_back(n);
		}
		return true;
	}
	return false;
}

/// Function: isConsistent
/// Description: Loops through both sorted vectors and ...
/// ... determines if vector a is always shorter than vector b
bool isConsistent(vector <int> & a, vector <int> & b) {
	for (size_t i = 0; i < a.size(); i++) {
		if (a[i] >= b[i]) return false;
	}
	return true;
}

/// Function: main
/// Description: main driver
int main() {
	
	vector <int> golds;
	vector <int> blues;

	/* Read both lines in */
	while (read_numbers(golds)) {
		read_numbers(blues);

		/* Sort vectors */
		sort(golds.begin(), golds.end());
		sort(blues.begin(), blues.end());

		/* Display if consistent or not */
		if (isConsistent(golds, blues)) cout << "Yes";
		else cout << "No";
		cout << endl;

	}

	return 0;

}
