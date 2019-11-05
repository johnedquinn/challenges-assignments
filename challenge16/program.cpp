/*
 * File: program.cpp
 * Author: John Ed Quinn
*/

/* PREAMBLE */
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <functional>
#include <bits/stdc++.h>
using namespace std;

// @struct	:	findShortestPaths
// @desc		:	uses Dijkstra's algorithm
struct Graph {
	vector <char> v;
	set <int> exits;
	int rows;
	int cols;
};

// @name	:	main
// @name	:	main
bool getInput(Graph & g) {
	g.v.clear(); g.exits.clear();
	if (cin >> g.rows >> g.cols && g.rows != 0 && g.cols != 0) {
		char c;
		for (size_t i = 0; i < g.rows; i++) {
			for (size_t j = 0; j < g.cols; j++) {
				cin >> c;
				g.v.push_back(c);
				if (c == 'E') g.exits.insert(i*g.cols + j);
			}
		}
		return true;
	}
	return false;
}

// @name	:	getAdjacents
// @desc	:	returns adjacent cells with weights
map <int, int> getAdjacents(Graph & g, int location) {
	map <int, int> m;
	bool westOkay = location % g.cols != 0;
	bool eastOkay = location % g.cols != g.cols - 1;
	bool southOkay = location < g.cols * (g.rows - 1);
	bool seOkay = eastOkay && southOkay && g.v[location + g.cols + 1] != '1';
	bool swOkay = westOkay && southOkay && g.v[location + g.cols - 1] != '1';
	westOkay = westOkay && g.v[location - 1] != '1';
	eastOkay = eastOkay && g.v[location + 1] != '1';
	southOkay = southOkay && g.v[location + g.rows] != '1';
	if (westOkay) m[location - 1] = 1;
	if (eastOkay) m[location + 1] = 1;
	if (southOkay) m[location + g.rows] = 1;
	if (seOkay)   m[location + g.cols + 1] = 2;
	if (swOkay)   m[location + g.cols - 1] = 2;
	return m;
}

int getNearestExit(Graph & g, vector <int> & distances) {
	int shortest = INT_MAX;
	int nearest;
	for (auto n : g.exits) {
		if (distances[n] < shortest) {
			shortest = distances[n];
			nearest = n;
		}
	}
	return nearest;
}

void printPath(Graph & g, int exit) {
	
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

		for (auto u : getAdjacents(g, n)) {
			if (distances[u.first] > distances[n] + u.second) {
				distances[u.first] = distances[n] + u.second;
				frontier.push(make_pair(distances[u.first], u.first));
			}
		}
	}
	return distances;
}

void printVect(Graph & g) {
	for (int i = 0; i < g.rows * g.cols; i++) {
		cout << "Index " << i << " value: " << "'" << g.v[i] << "'" << endl;
	}
	cout << endl;
}

// @name	:	main
// @desc	:	main driver
int main(int argc, char * argv []) {
	Graph g;
	while (getInput(g)) {
		vector <int> distances = findShortestPaths(g, 0);
		int exit = getNearestExit(g, distances);
		cout << exit << endl;
		for (auto n : distances) cout << n << " ";
		cout << endl;
	}
	return 0;
}

