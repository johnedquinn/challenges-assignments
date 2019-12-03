/*
 * File: program.cpp
 * Author: John Ed Quinn
*/

/* PREAMBLE */
#include <iostream>
using namespace std;

// @func : getCol
// @desc : gets the col based on what layer and layer time are presented
unsigned int getCol (unsigned int layer, unsigned int layer_time, unsigned int target_time) {
	if (layer % 2 == 0) {
		// Look at cells to left
		for (unsigned int offset = 0; offset < layer; offset++)
			if (layer_time - offset == target_time) return layer - offset;
		
		for (unsigned int col = 0; col < layer - 1; col++)
			if (layer_time - layer - col == target_time) return col + 1;
	} else {
		// Look at all cells below
		for (unsigned int current = layer_time; current > layer_time - layer; current--)
			if (current == target_time) return layer;
		return layer - 1;
	}
	return 0;
}

// @func : getRow
// @desc : gets the row based on what layer and layer time are presented
unsigned int getRow (unsigned int layer, unsigned int layer_time, unsigned int target_time) {
	if (layer % 2 == 0) {
		// Look at all cells to left
		for (unsigned int current = layer_time; current > layer_time - layer; current--)
			if (current == target_time) return layer;
		return layer - 1;
	} else {
		// Look at cells below
		for (unsigned int offset = 0; offset < layer; offset++)
			if (layer_time - offset == target_time) return layer - offset;
		
		for (unsigned int col = 0; col < layer - 1; col++)
			if (layer_time - layer - col == target_time) return col + 1;
	}
	return 0;
}

// @func : printSolution
// @desc : gets the layer on a diagonal, gets the col/row ...
// ... based on the diagonal and prints the solution.
void printSolution (unsigned int time) {
	unsigned int layer = 1;
	unsigned int layer_time = 1;
	while (time > layer_time) {
		layer_time += 2 * layer;
		layer++;
	}
	unsigned int row = getRow(layer, layer_time, time);
	unsigned int col = getCol(layer, layer_time, time);
	cout << time << " = " << "(" << row << ", " << col << ")" << endl;
}


// @func : main
// @desc : X
int main(int argc, char * argv []) {
	unsigned int time;
	while (cin >> time) {
		printSolution(time);
	}
	return 0;
}

