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
using namespace std;

// @name	:	getInput
// @desc	: grabs user input
bool getInput(map <int, set<int>> & m, int & nodes) {
	m.clear();
	int edges;
	if (cin >> nodes >> edges && nodes != 0 && edges != 0) {
		int source, dest;
		for (size_t i = 0; i < edges; i++) {
			cin >> source >> dest;
			m[source].insert(dest);
			m[dest].insert(source);
		}
		return true;
	}
	return false;
}

// @name	:	findLongestPathRecur
// @desc	:	finds the longest path across the graph
int findLongestPathRecur(map <int, set<int>> & m, set <tuple<int, int>> visited_edges, int current) {
	// Make sure not visited
	bool paths = false;
	int max = -1;
	for (auto & u : m[current]) {
		// Look to see if any edges available
		if (!visited_edges.count(make_tuple(current, u))) {
			visited_edges.insert(make_tuple(current, u));
			visited_edges.insert(make_tuple(u, current));
			int p = findLongestPathRecur(m, visited_edges, u);
			if (p > max) { max = p; }
			paths = true;
		}
	}
	if (!paths) {
		return 0;
	}
	return 1 + max;
}


// @name	:	findStartingNodeRecur
// @desc	:	finds the starting node to use for finding the longest path
tuple <int, int> findStartingNodeRecur(map <int, set<int>> & m, set <tuple<int, int>> visited_edges, int current) {
	// Make sure not visited
	bool paths = false;
	int max = -1; int start = 0;
	for (auto & u : m[current]) {
		// Look to see if any edges available
		if (!visited_edges.count(make_tuple(current, u))) {
			visited_edges.insert(make_tuple(current, u));
			visited_edges.insert(make_tuple(u, current));
			tuple <int, int> p = findStartingNodeRecur(m, visited_edges, u);
			int length = get<0>(p);
			int node = get<1>(p);
			if (length > max) { max = length; start = node; }
			paths = true;
		}
	}
	if (!paths) {
		return make_tuple(0, current);
	}
	return make_tuple(1 + max, start);
}

// @name	:	findStartingNode
// @desc	:	returns the node on the outermost edge of graph
int findStartingNode(map <int, set<int>> & m, int origin) {
	set <tuple<int,int>> visited;
	tuple <int, int> info = findStartingNodeRecur(m, visited, origin);
	return get<1>(info);
}


// @name	:	findLongestPath
// @desc	:	finds the longest path across the graph. Need to loop because ...
// 					the graph might not be connected.
int findLongestPath(map <int, set<int>> & m, int nodes) {
	set <tuple<int,int>> visited;
	int max = 0;
	for (size_t i = 0; i < nodes; i++) {
		int start = findStartingNode(m, i);
		int length = findLongestPathRecur(m, visited, start);
		//cout << i << " " << start << " " << length << endl;
		if (length > max) { max = length; }//cout << " " << length << " " << start << endl; }
	}
	return max;
}

// @name	:	main
// @desc	:	idea is to choose a random node
int main(int argc, char * argv []) {
	// Get Input
	int nodes; map <int, set<int>> m;
	while (getInput(m, nodes)) {
		cout << findLongestPath(m, nodes) << endl;
	}
	return 0;
}

