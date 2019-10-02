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
#include <set>
#include <algorithm>
using namespace std;

/// Function: getInput
/// Description: loads in data from stdin
bool getInput(vector <int> & legos) {
	legos.clear();
	string input;
	if (getline(cin, input)) {
		int n;
		stringstream ss(input);
		int i = 1;
		while (ss >> n) {
			for (int j = 0; j < n; j++) legos.push_back(i);
			i++;
		}
		return true;
	}
	return false;
}

/// Function: getSolution
/// Description: determines how many 4x1 blocks would be needed. It does this by ...
/// ... moving from front (which is larger), grabbing a block, and looping from ...
/// ... the back (which is smaller) to add numbers until we have hit our desired 4 blocks.
int getSolution(vector <int> & legos) {
	auto lego = legos.end(); lego--;
	int fits = 0;
	int n = 0;
	while (legos.size()) {
		fits++;
		n = legos.back();
		legos.pop_back();
		auto possible = legos.begin();
		while (possible != legos.end()) {
			if (n == 4) break;
			if (n + *possible <= 4) {
				n += *possible;
				legos.erase(possible);
			} else {
				possible++;
			}
		}
	}
	return fits;
}

/// Function: main
/// Description: X
int main(int argc, char * argv []) {

	vector <int> legos;
	
	while (getInput(legos)) {

		sort(legos.begin(), legos.end());

		cout << getSolution(legos) << endl;
	}

	return 0;
}

