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
#include <queue>
#include <set>
#include<bits/stdc++.h> 
using namespace std;

struct Graph {
	map <int, set<pair <int, int>>> m;
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
			g.m[s].insert(make_pair(t, w));
			g.m[t].insert(make_pair(s, w));
		}
		return true;
	}
	return false;
}

void subtractPairs(Graph & g, int min, int left, int right) {
	//int scratch = 1000;
	//cout << "MIN: " << min << endl;
	auto it = find_if(g.m[left].begin(), g.m[left].end(), [right](const pair<int,int>& p ){ return p.first == right; });
	if (it != g.m[left].end()) {
		//cout << "FOUND" << endl;
		int newWeight = (*it).second - min;
        g.m[left].erase(it);
		g.m[left].insert(make_pair(right, newWeight));
	}
	auto jt = find_if(g.m[right].begin(), g.m[right].end(), [left](const pair<int,int>& p){ return p.first == left; });
	if (jt != g.m[right].end()) {
		int newWeight = (*jt).second - min;
        g.m[right].erase(jt);
		g.m[right].insert(make_pair(left, newWeight));
	}
}

int findFloor (Graph & g, map <int, int> & m) {
	int current = g.target; int next;
	int min = INT_MAX;
	while (current != g.source) {
		next = m[current];
		auto it = find_if(g.m[current].begin(), g.m[current].end(), [next](const pair<int,int>& p ){ return p.first == next; });
		int weight = (*it).second;
		if (weight != 0 && weight < min) min = weight;
		current = next;
	}
	//cout << "@@@@ MIN: " << min << endl;
	return min;
}

// @func : getInput
// @desc : X
int floorFlow (Graph & g, map <int, int> & m) {
	int min = findFloor(g, m);
	int current = g.target; int next;
	//cout << "MAP: ";
	while (current != g.source) {
		//cout << "--> " << current;
		next = m[current];
		subtractPairs(g, min, current, next);
		current = next;
	}
	//cout << "--> " << next << endl;
	return min;
}

// @func : getInput
// @desc : X
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
			//path.push_back(v);
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

// @func : main
// @desc : X
int getSolution (Graph & g) {
	map <int, int> path;
	int sum = 0;

	path = getPath(g);
	while (path.find(g.target) != path.end()) {
		//cout << "@@ LENGTH : " << path.size() << endl;
		// Subtract min edge capacity from all edges in path
		int floor = floorFlow(g, path);
		sum += floor;

		// Compute a path from source to sink
		path = getPath(g);
	}
	return sum;
}

// @func : main
// @desc : X
int main(int argc, char * argv []) {
	Graph g; size_t i = 1;
	while (getInput(g)) {
		cout << "Network: " << i++ << " Bandwidth: " << getSolution(g) << endl;
	}
	return 0;
}

