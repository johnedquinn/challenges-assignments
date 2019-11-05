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

// @struct	:	findShortestPaths
// @desc	:	uses Dijkstra's algorithm
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
		char c;

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


// @name	:	getAdjacents
// @desc	:	returns adjacent cells with weights
pair <int, int> locationToCoordinates(Graph & g, int location) {
	int col = location % g.cols;
	int row;
	for (int i = g.cols - 1; i > -1; i--) {
		if (location >= g.cols * i) {
			row = i;
			break;
		}
	}
	return make_pair(col, row);
}

int coordinatesToLocation(Graph & g, int col, int row) {
	return row * g.cols + col;
}

int coordinatesToLocation(Graph & g, pair <int, int> coord) {
	int col = coord.first; int row = coord.second;
	return coordinatesToLocation(g, col, row);
}

// @name	:	getAdjacents
// @desc	:	returns adjacent cells with weights
map <int, int> getWeightedAdjacents(Graph & g, pair <int, int> & coord) {
	map <int, int> m;
	int col = coord.first; int row = coord.second;
	//cout << "IN WEIGHTED ADJ; col = " << col << "; row = " << row << endl;
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

map <int, int> getWeightedAdjacents(Graph & g, int location) {
	//cout << "LOCATION: " << location << " ";
	pair<int, int> coord = locationToCoordinates(g, location);
	return getWeightedAdjacents(g, coord);
}

// @name	:	getAdjacents
// @desc	:	returns adjacent cells with weights
set <pair<int, int>> getAdjacents(Graph & g, pair <int, int> & coord) {
	set <pair<int, int>> s;
	int x = coord.first; int y = coord.second;
	s.insert(make_pair(x-1, y));
	s.insert(make_pair(x+1, y));
	s.insert(make_pair(x, y-1));
	s.insert(make_pair(x, y+1));
	s.insert(make_pair(x-1, y-1));
	s.insert(make_pair(x-1, y+1));
	s.insert(make_pair(x+1, y-1));
	s.insert(make_pair(x+1, y+1));
	return s;
}

set <pair<int, int>> getAdjacents(Graph & g, int location) {
	pair <int, int> coord = locationToCoordinates(g, location);
	return getAdjacents(g, coord);
}

int getNearestExit(Graph & g, vector <int> & distances) {
	int shortest = INT_MAX;
	int nearest = -1;
	for (auto n : g.exits) {
		//cout << "N: " << n << "; distance = " << distances[n];
		if (distances[n] < shortest) {
			shortest = distances[n];
			nearest = n;
			//cout << " updated";
		}
		//cout << endl;
	}
	return nearest;
}

int convertLocation(Graph & g, int location) {
	pair <int, int> old = locationToCoordinates(g, location);
	old.first -= 1; old.second -= 1;
	g.rows -= 2; g.cols -=2;
	int newLoc = coordinatesToLocation(g, old);
	g.rows += 2; g.cols +=2;
	return newLoc;
}

/*int getMin(Graph & g, vector <int> & distances, int location) {
	int min = INT_MAX;
	int min_index = g.rows*g.cols;
	//cout << endl << "@@@@@@@@@@@@@@@@ LOCATION: " << location << "/" << convertLocation(g, location) << endl;
	for (auto e: getAdjacents(g, location)) {
		//cout << "@@ MIN = " << min << "; MIN_INDEX = " << min_index << "/" << convertLocation(g, min_index) << endl;
		int dist = distances[coordinatesToLocation(g,e)];
		int loc = coordinatesToLocation(g,e);
		//cout << "   Evaluating: " << loc << "/" << convertLocation(g,loc) << "; VAL = " << dist << endl;
		if (dist < min) {
			min = dist;
			//cout << "A) CHOOSING " << loc << "/" << convertLocation(g, loc) << "; VAL = " << dist << endl;
			min_index = loc;
		} else if (dist == min) {
			if (convertLocation(g, loc) < convertLocation(g, min_index)) {
				min_index = loc;
				//cout << "B) CHOOSING " << loc << "/" << convertLocation(g, loc) << "; VAL = " << dist << endl;
			}
		}
	}
	return min_index;
}*/

int getMin(Graph & g, vector <int> & distances, int location) {
	int min = INT_MAX;
	int min_index = g.rows*g.cols;
	//cout << endl << "@@@@@@@@@@@@@@@@ LOCATION: " << location << "/" << convertLocation(g, location) << endl;
	for (auto e: getAdjacents(g, location)) {
		//cout << "@@ MIN = " << min << "; MIN_INDEX = " << min_index << "/" << convertLocation(g, min_index) << endl;
		int dist = distances[coordinatesToLocation(g,e)];
		int loc = coordinatesToLocation(g,e);
		//cout << "   Evaluating: " << loc << "/" << convertLocation(g,loc) << "; VAL = " << dist << endl;
		if (dist < min) {
			min = dist;
			//cout << "A) CHOOSING " << loc << "/" << convertLocation(g, loc) << "; VAL = " << dist << endl;
			min_index = loc;
		} else if (dist == min) {
			if (convertLocation(g, loc) < convertLocation(g, min_index)) {
				min_index = loc;
				//cout << "B) CHOOSING " << loc << "/" << convertLocation(g, loc) << "; VAL = " << dist << endl;
			}
		}
	}
	return min_index;
}

/*void printPath(Graph & g, vector <int> & distances, int exit) {
	int current = exit;
	stack <int> path;
	while (current != g.start) {
		int converted = convertLocation(g, current);
		path.push(converted);
		current = getMin(g, distances, current);
	}
	while (!path.empty()) {
		cout << " " << path.top(); path.pop();
	}
}*/

stack <int> getPath(Graph & g, int exit) {
	int current = exit;
	stack <int> path;
	while (current != g.start) {
		path.push(current);
		current = g.path[current];
	}
	return path;
}

void printPath(Graph & g, stack <int> & path) {
	while (!path.empty()) {
		cout << " " << convertLocation(g, path.top());
		path.pop();
	}
}

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
		//cout << "TOP: " << n << "; VAL = " << distances[n] << endl;

		if (marked.count(n)) continue;

		marked.insert(n);

		for (auto u : getWeightedAdjacents(g, n)) {
			//cout << "u-first = " << u.first << "; u-second = " << u.second << endl;
			if (distances[u.first] > distances[n] + u.second) {
				g.path[u.first] = n;
				distances[u.first] = distances[n] + u.second;
				frontier.push(make_pair(distances[u.first], u.first));
			} else if (distances[u.first] == distances[n] + u.second && n < g.path[u.first]) {
				g.path[u.first] = n;
			}
		}
	}
	//for (auto n : distances) cout << n << " "; cout << endl;
	/*for (size_t row = 0; row < g.rows; row++) {
		for (size_t col = 0; col < g.cols; col++)
			cout << distances[coordinatesToLocation(g, col, row)] << " ";
		cout << endl;
	}*/
	return distances;
}

void getSolution(Graph & g) {
	vector <int> distances = findShortestPaths(g, g.start);
	/*if (g.start == -1) {
		cout << "Cost: 0 Path: None" << endl;
		return;
	}*/
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

