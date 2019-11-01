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
#include <bitset>
using namespace std;

// @name: getInput
// @desc: X
bool getInput(string & s, int & target) {
	s.clear();
	if (cin >> target) {
		cin >> s;
		return true;
	}
	return false;
}

// @name: convertInt
// @desc: X
string convertInt(int n) {
	if (n == 0) return "0";
	bitset<16> b (n);
	string s = b.to_string();
	while (s[0] == '0') s.erase(0,1);
	return s;
}

// @name: getNumPaths
// @desc: X
int getNumPaths(string & s, string & target, string str, int index) {
	if (index >= s.length()) return 0;
	int total = 0;
	str += s[index];
	if (str.length() == target.length()) {
		if (str == target) {
			total = 1;
		}
		str.erase(0, 1);
	}
	return total + getNumPaths(s, target, str, 2*index + 1) + getNumPaths(s, target, str, 2*index + 2);
}

// @name: main
// @desc: X
int main(int argc, char * argv []) {
	string s;
	int t;
	while (getInput(s, t)) {
		string target = convertInt(t);
		cout << "Paths that form " << t << " in binary (" << target << "): " << getNumPaths(s, target, "", 0) << endl;
	}
	return 0;
}

