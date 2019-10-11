/*
 * File: prog.cpp
 * Author: John Ed Quinn
*/

/* PREAMBLE */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
using namespace std;

/// Function: createPermutation
/// Description: Creates permutations of length 5
void createPermutation(string & num_str, vector <string> & v, set <char> & s) {
	if (num_str.length() == 5) {
		v.push_back(num_str);
	} else {
		auto n = s;
		for (auto e : n) {
			num_str.push_back(e);
			s.erase(e);
			createPermutation(num_str, v, s);
			s.insert(e);
			num_str.pop_back();
		}
	}
}


/// Function: generateSecondNumber
/// Description: Generates the string that the second number would be represented by
string generateSecondNumber(int first, int goal) {
	int second = first / goal;
	string s;
	for (int i = 4; i > -1; i--) {
		int remainder = second % 10;
		second /= 10;
		char c = '0' + remainder;
		s.insert(0, 1, c);
	}
	return s;
}

/// Function: checkIfUnique
/// Description: Checks both numbers to see if either of them has duplicate numbers
bool checkIfUnique(string s1, string s2) {
	int n [10] = {0};
	for (auto c : s1) {
		int a = c - '0';
		n[a]++;
	}
	for (auto c : s2) {
		int a = c - '0';
		if (n[a] > 0) return false;
		else n[a]++;
	}
	return true;
}


/// Function: checkDivisions
/// Description: Loop through permuations, and if that number is divisible by the goal, ...
/// ... then create the possible second number and convert it to a string. Then check if ...
/// ... both strings don't contain duplicates. If all checks out, print out the results. If no ...
/// ... matches, print appropriate message.
void checkDivisions(vector <string> & v, int goal, int & i) {
	/* Fix spacing */
	i++;
	if (i > 1) cout << endl;

	/* Search for match */
	bool found = false;
	for (auto e : v) {
		if (stoi(e) % goal == 0) {
			string s2 = generateSecondNumber(stoi(e), goal);
			if (checkIfUnique(e, s2)) {
			 found = true;
			 cout << e << " / " << s2 << " = " << goal << endl;
			}
		}
	}
	if (found == false) { cout << "There are no solutions for " << goal << "." << endl; }
}

/// Function: main
/// Description: Main driver. Take a number from user and check the permutations vector for matches.
int main(int argc, char * argv []) {

	set <char> s = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	string str;
	vector <string> v;
	createPermutation(str, v, s);

	int n, i = 0;
	while (cin >> n) {
		if (n == 0) break;
		checkDivisions(v, n, i);
	}

	return 0;
}

