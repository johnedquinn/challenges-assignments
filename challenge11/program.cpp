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
#include <numeric>
#include<bits/stdc++.h>

using namespace std;

/// Function: getInput
/// Description: get input and insert into grid with boundaries of infinity
bool getInput(vector<vector<unsigned int>> & v, size_t & size) {
	v.clear();
	unsigned int num;
	if (cin >> size && size != 0) {

		/* Resize grid and set boundaries to infinity */
		v.resize(size + 2);
		for (auto & subv : v) subv.push_back(INT_MAX);
		for (size_t i = 0; i <= size + 1; i++) v[0].push_back(INT_MAX);
		for (size_t i = 0; i <= size + 1; i++) v[size + 1].push_back(INT_MAX);

		/* Insert elements into array */
		for (unsigned int i = 1; i <= size; i++) {
			for (unsigned int j = 1; j <= size; j++) {
				cin >> num;
				v[i].push_back(num);
			}
		}
		/* Insert infinity to bottom row */
		for (auto & subv : v) subv.push_back(INT_MAX);
		return true;
	}
	return false;
}

/// Function: getQuantGrid
/// Description: get newly quantified grid, where each square represents ...
/// ... how many Kakamora have been seen from the first square to that square.
void getQuantGrid(vector <vector <unsigned int>> & v, size_t size) {
	for (size_t col = 1; col <= size; col++) {
		for (size_t row = 1; row <= size; row++) {
			/* Look around */
			int left = v[col - 1][row];
			int above = v[col][row - 1];
			int diag = v[col - 1][row - 1];
			/* Get Minimum */
			int min = left < above ? left : above;
			min = min < diag ? min : diag;
			/* Edit graph */
			if (min != INT_MAX) v[col][row] += min;
		}
	}
}

/// Function: getPath
/// Description: get the path using new grid
vector <int> getPath(vector <vector <unsigned int>> & v, size_t size) {
	vector <int> path;
	int col = size, row = size;
	/* Traverse through grid */
	while (col != 0 && row != 0) {
		int min = INT_MAX;
		int nextCol = col; int nextRow = row;
		/* Look above */
		if (v[col][row - 1] < min) {
			min = v[col][row - 1];
			nextCol = col; nextRow = row - 1;
		}
		/* Look diag */
		if (v[col - 1][row - 1] < min) {
			min = v[col - 1][row - 1];
			nextCol = col - 1; nextRow = row - 1;
		}
		/* Look left */
		if (v[col - 1][row] < min) {
			min = v[col - 1][row];
			nextCol = col - 1; nextRow = row;
		}
		/* Insert and update location */
		if (min == INT_MAX) break;
		path.insert(path.begin(), v[col][row] - v[nextCol][nextRow]);
		col = nextCol; row = nextRow;
	}
	path.insert(path.begin(), v[1][1]);
	return path;
}

/// Function: main
/// Description: main driver for Kakamora
int main(int argc, char * argv []) {

	vector <vector<unsigned int>> v;
	size_t size;
	while (getInput(v, size)) {

		/* Create new grid and get path */
		getQuantGrid(v, size);
		vector <int> path = getPath(v, size);

		/* Print Path */
		cout << accumulate(path.begin(), path.end(), 0) << endl;
		cout << path[0];
		for (auto it = path.begin() + 1; it < path.end(); it++) cout << " " << *it; cout << endl;

	}
	
	return 0;
}