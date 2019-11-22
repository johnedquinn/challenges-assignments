/*
 * File: program.cpp
 * Author: John Ed Quinn
*/

/* PREAMBLE */
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include<bits/stdc++.h> 
using namespace std;

struct Graph {
	map <int, map<int, int>> m;
	int source; int target;
};

// @func : getInput
// @desc : X
bool getInput (Graph & g) {
	g.m.clear();
	int n;
	if (cin >> n && n != 0) {
		int connections;
		cin >> g.source >> g.target >> connections;
		for (size_t i = 0; i < connections; i++) {
			int s, t, w;
			cin >> s >> t >> w;
			g.m[s][t] += w;
			g.m[t][s] += w;
		}
		return true;
	}
	return false;
}

// @func : findFloor
// @desc : get min flow
int findFloor (Graph & g, map <int, int> & m) {
	int current = g.target; int next;
	int min = INT_MAX;
	while (current != g.source) {
		next = m[current];
		int weight = g.m[current][next];
		if (weight != 0 && weight < min) min = weight;
		current = next;
	}
	return min;
}

// @func : floorFlow
// @desc : return min flow and decrease flow between vertices
int floorFlow (Graph & g, map <int, int> & m) {
	int min = findFloor(g, m);
	int current = g.target; int next;
	while (current != g.source) {
		next = m[current];
		g.m[current][next] -= min;
		g.m[next][current] -= min;
		current = next;
	}
	return min;
}

// @func : getPath
// @desc : BFS to get path
map <int, int> getPath (Graph & g) {
	queue<int> frontier; frontier.push(g.source);
	set <int> visited;
	map <int, int> path;

	// While Frontier
	while (!frontier.empty()) {

		// Current vertex
		int v = frontier.front(); frontier.pop();

		// Check if target
		if (v == g.target) {
			return path;
		}

		// Check if in visited
		if (visited.count(v)) continue;
		visited.insert(v);

		for (auto neighbor : g.m[v]) {
			if (!visited.count(neighbor.first) && neighbor.second > 0) {
				path[neighbor.first] = v;
				frontier.push(neighbor.first);
			}
		}
	}
	map <int, int> empty;
	return empty;
}

// @func : getSolution
// @desc : Keep doing BFS till done and decrease flows
int getSolution (Graph & g) {
	map <int, int> path;
	int sum = 0;

	path = getPath(g);
	while (path.find(g.target) != path.end()) {
		// Subtract min edge capacity from all edges in path
		int floor = floorFlow(g, path);
		sum += floor;

		// Compute a path from source to sink
		path.clear();
		path = getPath(g);
	}
	return sum;
}

// @func : main
// @desc : main driver
int main(int argc, char * argv []) {
	Graph g; size_t i = 1;
	while (getInput(g)) {
		cout << "Network " << i++ << ": Bandwidth is " << getSolution(g) << "." << endl;
	}
	return 0;
}

