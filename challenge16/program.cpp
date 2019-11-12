/*
 * File: program.cpp
 * Author: John Ed Quinn
*/

/* PREAMBLE */
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <unordered_map>
#include <functional>
#include <bits/stdc++.h>
#include <stack>
#include <algorithm>
using namespace std;

// @struct	:	Graph
// @desc	:	For passing data around
struct Graph {
	vector <vector <char>> states;
	unordered_map <int, int> path;
	int start = -1;
	set <int> exits;
	int rows;
	int cols;
};

// @name	:	getInput
// @desc	:	gets user input
bool getInput(Graph & g) {
	g.states.clear(); g.exits.clear();
	if (cin >> g.rows >> g.cols && g.rows != 0 && g.cols != 0) {
		g.rows += 2; g.cols += 2;

		// Make top row all 1's
		g.states.resize(g.cols);
		for (auto & v : g.states) {
			v.push_back('1');
		}
		// Make sides all 1's
		for (size_t i = 0; i < g.rows-2; i++) {
			g.states[0].push_back('1');
			g.states[g.cols - 1].push_back('1');
		}

		// Insert information into matrix
		for (size_t i = 1; i < g.rows - 1; i++) {
			for (size_t j = 1; j < g.cols - 1; j++) {
				char c;
				cin >> c;
				if (c == 'S') {
					g.start = i * (g.cols) + j;
				}
				if (c == 'E') {
					g.exits.insert(i * g.cols + j);
					g.states[j].push_back('0');
				} else
				g.states[j].push_back(c);
			}
		}

		for (auto & v : g.states) v.push_back('1');
		return true;
	}
	return false;
}

// @name	:	locationToCoordinates
// @desc	:	Helpful to get access to where in the matrix it is
pair <int, int> locationToCoordinates(Graph & g, int location) {
	int col = location % g.cols;
	int row;
	for (int i = 0; i < g.rows; i++) {
		if (i*g.cols <= location && location < i*g.cols + g.cols) {
			return make_pair(col, i);
		}
	}
	return make_pair(col, 1);
}

// @name	:	coordinatesToLocation
// @desc	:	converting from the matrix to the distances vector locations
int coordinatesToLocation(Graph & g, int col, int row) {
	return row * g.cols + col;
}

// @name	:	coordinatesToLocation
// @desc	:	converting from the matrix to the distances vector locations
int coordinatesToLocation(Graph & g, pair <int, int> coord) {
	int col = coord.first; int row = coord.second;
	return coordinatesToLocation(g, col, row);
}

// @name	:	getWeightedAdjacents
// @desc	:	returns adjacent cells with weights
map <int, int> getWeightedAdjacents(Graph & g, pair <int, int> & coord) {
	map <int, int> m;
	int col = coord.first; int row = coord.second;
	if (g.states[col-1][row] == '0') m[coordinatesToLocation(g, col-1, row)] = 1;
	if (g.states[col+1][row] == '0') m[coordinatesToLocation(g, col+1, row)] = 1;
	if (g.states[col][row-1] == '0') m[coordinatesToLocation(g, col, row-1)] = 1;
	if (g.states[col][row+1] == '0') m[coordinatesToLocation(g, col, row+1)] = 1;
	if (g.states[col-1][row-1] == '0') m[coordinatesToLocation(g, col-1, row-1)] = 2;
	if (g.states[col-1][row+1] == '0') m[coordinatesToLocation(g, col-1, row+1)] = 2;
	if (g.states[col+1][row-1] == '0') m[coordinatesToLocation(g, col+1, row-1)] = 2;
	if (g.states[col+1][row+1] == '0') m[coordinatesToLocation(g, col+1, row+1)] = 2;
	return m;
}

// @name	:	getWeightedAdjacents
// @desc	:	returns adjacent cells with weights
map <int, int> getWeightedAdjacents(Graph & g, int location) {
	pair<int, int> coord = locationToCoordinates(g, location);
	return getWeightedAdjacents(g, coord);
}

// @name	:	getNearestExit
// @desc	:	determine what path to take
int getNearestExit(Graph & g, vector <int> & distances) {
	int shortest = INT_MAX;
	int nearest = -1;
	for (auto n : g.exits) {
		if (distances[n] < shortest) {
			shortest = distances[n];
			nearest = n;
		}
	}
	return nearest;
}

// @name	:	convertLocation
// @desc	:	convert location from matrix with surrounding 1s to without 1s
int convertLocation(Graph & g, int location) {
	pair <int, int> old = locationToCoordinates(g, location);
	old.first -= 1; old.second -= 1;
	g.rows -= 2; g.cols -=2;
	int newLoc = coordinatesToLocation(g, old);
	g.rows += 2; g.cols +=2;
	return newLoc;
}

// @name	:	findShortestPaths
// @desc	:	uses Dijkstra's algorithm
stack <int> getPath(Graph & g, int exit) {
	int current = exit;
	stack <int> path;
	while (current != g.start) {
		path.push(current);
		current = g.path[current];
	}
	return path;
}

// @name	:	printPath
// @desc	:	take in a path and output it
void printPath(Graph & g, stack <int> & path) {
	while (!path.empty()) {
		cout << " " << convertLocation(g, path.top());
		path.pop();
	}
}

// @name	:	printInfo
// @desc	:	print information regarding the cost and path
void printInfo(Graph & g, vector <int> & distances) {
	int exit = getNearestExit(g, distances);
	if (exit < 0) {
		cout << "Cost: 0 Path: None" << endl;
		return;
	}
	cout << "Cost: " << distances[exit] << " ";
	cout << "Path: ";
	cout << convertLocation(g, g.start);
	stack <int> path = getPath(g, exit);
	printPath(g, path);
	cout << endl;
}

// @name	:	findShortestPaths
// @desc	:	uses Dijkstra's algorithm
vector <int> findShortestPaths(Graph & g, int start) {
	vector <int> distances(g.rows * g.cols, INT_MAX);
	priority_queue <pair<int, int>, vector <pair<int, int>>, greater<pair <int, int>>> frontier;
	set <int> marked;
	frontier.push(make_pair(0, start));
	distances[start] = 0;

	while (!frontier.empty()) {
		int n = frontier.top().second; frontier.pop();

		if (marked.count(n)) continue;

		marked.insert(n);

		for (auto u : getWeightedAdjacents(g, n)) {
			if (distances[u.first] > distances[n] + u.second) {
				g.path[u.first] = n;
				distances[u.first] = distances[n] + u.second;
				frontier.push(make_pair(distances[u.first], u.first));
			} else if (distances[u.first] == distances[n] + u.second && n < g.path[u.first]) {
				g.path[u.first] = n;
				frontier.push(make_pair(distances[u.first], u.first));
			}
		}
	}
	return distances;
}

// @name	:	findShortestPaths
// @desc	:	uses Dijkstra's algorithm
void getSolution(Graph & g) {
	vector <int> distances = findShortestPaths(g, g.start);
	if (g.start == -1) {
		cout << "Cost: 0 Path: None" << endl;
		return;
	}
	printInfo(g, distances);
}

// @name	:	main
// @desc	:	main driver
int main(int argc, char * argv []) {
	Graph g;
	while (getInput(g)) {
		getSolution(g);
	}
	return 0;
}