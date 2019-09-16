/*
 * File: challenge01/program.cpp
 * Author: John Ed Quinn
 * Time Complexity: O(n)
 * Space Complexity: O()
 */

/* PREAMBLE */
#include <iostream>
#include <string>
#include <unordered_map>
#include <climits>

using namespace std;

/* PROTOTYPES */
size_t getNumPairs(string & s1, string & s2);
void fillMap(unordered_map <char, int> & map, string & s);
void fillAndCheckMap(unordered_map <char, int> & map1, unordered_map <char, int> & map2, string & s1);
size_t compareMaps(unordered_map <char, int> & map1, unordered_map <char, int> & map2);

/// Function: main
/// Description: grabs input and determines how many times s2 can be ...
/// ... made from s1
int main () {

	string s1, s2;
	while (cin >> s1) {
		cin >> s2;
		cout << getNumPairs(s1, s2) << endl;
	}

	return 0;
}

/// Function: getNumPairs
/// Description: compares the two strings and returns the number ...
/// ... of times s2 can be formed out of letters in s1 (without repeating)
size_t getNumPairs(string & s1, string & s2) {

	if (s2.length() == 0 || s1.length() == 0) return 0;

	// Get number of chars from s2
	unordered_map <char, int> map2;
	fillMap(map2, s2);

	// Get number of matching chars to map2
	unordered_map <char, int> map1;
	fillAndCheckMap(map1, map2, s1);

	// Determine number of matches
	return compareMaps(map1, map2);
}

/// Function: fillMap
/// Description: fills map2
void fillMap(unordered_map <char, int> & map, string & s) {
	for (auto c : s) {
		map[c] = map[c] + 1;
	}
}

/// Function: fillAndCheckMap
/// Description: moves through s1 and checks if char is a key in map2; If ...
/// ... so, add to map1
void fillAndCheckMap(unordered_map <char, int> & map1, unordered_map <char, int> & map2, string & s1) {
	for (auto c: s1) {
		if (map2.find(c) != map2.end()) {
			map1[c] = map1[c] + 1;
		}
	}
}

/// Function: compareMaps
/// Description: decides how many times s2 can be made from s1 by checking the maps
size_t compareMaps(unordered_map <char, int> & map1, unordered_map <char, int> & map2) {
	if (map1.size() != map2.size()) return 0;
	size_t max = UINT_MAX;
	for (auto e : map1) {
		size_t size = map1[e.first] / map2[e.first];
		max = (max > size) ? size : max;
	}
	return max;
}
