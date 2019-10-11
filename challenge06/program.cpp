/*
 * File: challenge06/program.cpp
 * Author: John Ed Quinn
*/

/* PREAMBLE */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
using namespace std;

/// Function: read_fruits
/// Description: Get each line of user input ...
/// ... and split the words into a vector
bool read_fruits(vector <string> & v) {
  v.clear();
  string line;
  if (getline(cin, line)) {
    stringstream ss(line);
    string fruit;
    while (ss >> fruit) {
			v.push_back(fruit);
    }
		return true;
  }
	return false;
}

/// Function: getSubSequence
/// Description: Determine the size of the subsequence ...
/// ... and the index of the first string in the subsequence.
vector <int> getSubsequence(vector <string> & v) {
	set <string> s;
	int max = 0, index = 0;
	for (int i = 0; i < v.size(); i++) {
		s.clear();
		for (int j = i; j < v.size(); j++) {
			if (s.find(v[j]) != s.end())
				break;
			s.insert(v[j]);
			index = (max < j - i + 1) ? i : index;
			max = (max < j - i + 1) ? j - i + 1 : max;
		}
	}
	vector <int> soln = {max, index};
	return soln;
}

/// Function: main
/// Description: Get user input of fruits, then for each line loop ...
/// ... through them and determine the longest subsequence 
int main(int argc, char * argv []) {
	vector <string> fruits;
	while (read_fruits(fruits)) {

		vector <int> soln = getSubsequence(fruits);
		cout << soln[0] << ": ";
		for (int i = soln[1]; i < soln[1] + soln[0] - 1; i++) {
			cout << fruits[i] << ", ";
		}
		cout << fruits[soln[1] + soln[0] - 1] << endl;

	}
	return 0;
}

