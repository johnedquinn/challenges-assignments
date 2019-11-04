/*
 * File: program.cpp
 * Author: John Ed Quinn
*/

/* PREAMBLE */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <cmath>
using namespace std;

struct Node {
	int data;
	Node * left;
	Node * right;
};

// @name: getInput
// @desc: X
bool getInput(vector <int> & v) {
	v.clear();
	string input;
	if (getline(cin, input)) {
		stringstream ss(input);
		int n;
		while (ss >> n) { v.push_back(n); }
		return true;
	}
	return false;
}

// @name: firstNode
// @desc: X
Node * firstNode(Node * n, int level) {
	if (!n) return NULL;
	if (level == 1) {
		return n;
	}
	return firstNode(n->left, level-1);
}

// @name: printLevel
// @desc: X
bool printLevel(Node * n, int level, Node * leftest) {
	if (!n) return false;
	if (level == 1) {
		if (n != leftest) cout << " ";
		cout << n->data;
		return true;
	}
	bool left = printLevel(n->left, level - 1, leftest);
	bool right = printLevel(n->right, level - 1, leftest);
	return left || right;
}

// @name: printLevels
// @desc: X
void printLevels(Node * n) {
	int level = 1;
	Node * leftest;
	while (leftest = firstNode(n, level)) {
		printLevel(n, level, leftest);
		level++;
		cout << endl;
	}
}

// @name: createBEST
// @desc: X
Node * createBST(vector <int> & v, int low, int high) {
	if (low > high) return NULL;
	Node * n = new Node;
	int mid = ceil((high+low)/2.0);
	n->data = v[mid];
	n->left = createBST(v, low, mid-1);
	n->right = createBST(v, mid+1, high);
	return n;
}

// @name: createBST
// @desc: X
Node * createBST(vector <int> & v) {
	return createBST(v, 0, v.size()-1);
}

// @name: main
// @desc: X
int main(int argc, char * argv []) {
	vector <int> v;
	while (getInput(v)) {
		Node n;
		n.right = createBST(v);
		printLevels(n.right);
	}
	return 0;
}

