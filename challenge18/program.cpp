/*
 * File: program.cpp
 * Author: John Ed Quinn
*/

/* PREAMBLE */
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
using namespace std;

// @struct : Graph
// @desc   : Stores necessary info to pass around
struct Graph {
	map <int, int> degrees;
	map <int, set <int>> adj;
};


// @name : getSoln
// @desc : performs topological sort
void getSoln(Graph & g) {

	// Declare frontier and visited
	queue <int> frontier;
	vector <int> visited;

	// Add all nodes with degree 0
	for (auto e : g.degrees) {
		if (e.second == 0) frontier.push(e.first);
	}

	// Get all items in graph
	while (!frontier.empty()) {

		int n = frontier.front(); frontier.pop();
		visited.push_back(n);

		// Loop through neighbors and add to frontier, if needed
		for (auto e : g.adj[n]) {
			g.degrees[e] -= 1;
			if (g.degrees[e] == 0) {
				frontier.push(e);
			}
		}

	}

	// Output solution
	for (auto n : visited) cout << n; cout << endl;

}

// @name : getInput
// @desc : Gets input from user and adds to adjacency list and degree mapping
void getInput(Graph & g) {
	string s;
	while (cin >> s) {
		for (int i = 0; i < 2; i++) {
			int first = s[i] - '0'; int second = s[i+1] - '0';
			if (g.degrees.find(first) == g.degrees.end()) g.degrees[first] = 0;
			if (g.degrees.find(second) == g.degrees.end()) g.degrees[second] = 0;
			if (g.adj[first].find(second) == g.adj[first].end()) g.degrees[second] += 1;
			g.adj[first].insert(second);
		}
	}
}

// @name : main
// @desc : main driver for program
int main(int argc, char * argv []) {
	Graph g;
	getInput(g);
	getSoln(g);
	return 0;
}

