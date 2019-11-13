/*
 * File: program.cpp
 * Author: John Ed Quinn
*/

/* PREAMBLE */
#include <iostream>
#include <vector>
#include <set>
#include <cfloat>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <iomanip>
using namespace std;

// @struct : Graph
// @desc   : X
struct Graph {
	unordered_map <int, pair<float, float>> buildings;
};

// @name : getInput
// @desc : gets input from user
bool getInput(Graph & g) {
	g.buildings.clear();
	int num;
	if (cin >> num && num != 0) {
		float x, y;
		for (size_t i = 0; i < num; i++) {
			cin >> x >> y;
			g.buildings[i] = make_pair(x, y);
		}
		return true;
	}
	return false;
}

// @name : getMST
// @desc : X
float getDist(pair<float, float> a, pair <float, float> b) {
	return sqrt((float)pow(b.second - a.second, 2.0) + (float)pow(b.first - a.first, 2.0));
}

float getTotalLength(vector <float> & v) {
	float total = 0;
	for (auto f : v) total += f;
	return total;
}

// @name : getMST
// @desc : X
void getMST(Graph & g) {
	priority_queue <pair<float, float>, vector <pair<float, float>>, greater<pair <float, float>>> frontier;
	set <int> visited;
	frontier.push(make_pair(0, 0));
	vector <float> lengths(g.buildings.size(), FLT_MAX);
	lengths[0] = 0;

	while (!frontier.empty()) {
		int n = frontier.top().second;
		float weight = frontier.top().first;
		frontier.pop();
		if (visited.count(n)) continue;
		
		visited.insert(n);

		for (auto e : g.buildings) {
			if (e.first == n) continue;
			int neighbor = e.first;
			float cost = getDist(g.buildings[n], e.second);
			if (!visited.count(neighbor) && lengths[neighbor] > cost) {
				lengths[neighbor] = cost;
			}
			frontier.push(make_pair(cost, neighbor));
		}
	}
	cout << fixed << setprecision(2);
	cout << getTotalLength(lengths) << endl;
}

// @name : main
// @desc : X
int main(int argc, char * argv []) {
	Graph g;
	while (getInput(g)) {
		getMST(g);
	}
	return 0;
}

