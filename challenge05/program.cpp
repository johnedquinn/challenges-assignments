/*
 * File: challenge05/program.cpp
 * Author: John Ed Quinn
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

/// Function: numOccurrences
/// Description: Determines the number of cycles a given ...
/// ... input will take going through a function. If there is no current ...
/// ... value in the unordered_map that contains the input, then add to the map.
unsigned int numOccurrences(unsigned int input, unordered_map <unsigned int, unsigned int> & map) {
	if (input == 1) return 1;

	auto e = map.find(input);
	if (e != map.end()) return (*e).second;

	if (input % 2) input = 3 * input + 1;
	else input /= 2;

	unsigned int output = numOccurrences(input, map);
	map.insert({input, output});

	return output + 1;
}


/// Function: main
/// Description: Get the 2 numbers from user, loop between the two numbers, and ...
/// ... determines the number of cycles for each number. It then compares to the ...
/// ... current max and updates accordingly.
int main() {
	unsigned int first, second;
	unordered_map<unsigned int, unsigned int> map;
	while (cin >> first) {
		cin >> second;
		unsigned int i = first;
		unsigned int max = 0, index = 0;
		while (i != second) {
			unsigned int out = numOccurrences(i, map);
			if (out > max) {
				max = out;
				index = i;
			}
			if (i > second) i--;
			else i++;
		}
		cout << first << " " << second << " " << index << " " << max << endl;
	}
	return 0;
}
