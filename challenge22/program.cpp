/*
 * File: program.cpp
 * Author: John Ed Quinn
*/

/* PREAMBLE */
#include <iostream>
#include <string>
using namespace std;

// @enum : Oper
// @desc : holds the operands
enum Oper {
	NONE=0,
	MULT,
	ADD,
	SUB,
	DIV
};

// @func : parseOperand
// @desc : returns the appropriate operand
Oper parseOperand(char c) {
	switch (c) {
		case '*':
			return MULT;
		case '+':
			return ADD;
		case '-':
			return SUB;
		case '/':
			return DIV;
		default:
			return NONE;
	}
	return NONE;
}

// @func : performOperation
// @desc : performs operations on the two passed integers
int performOperation(int value, int temp_value, Oper oper) {
	switch (oper) {
		case NONE:
			return temp_value;
		case MULT:
			return value * temp_value;
		case ADD:
			return value + temp_value;
		case SUB:
			return value - temp_value;
		case DIV:
			return value / temp_value;
		default:
			return temp_value;
	}
	return temp_value;
}

// @func : getValue
// @desc : recursively and iteratively determine value
int getValue (string & line, int & index) {
	/* Define held value and operation */
	int value = 0;
	Oper oper = NONE;

	/* Iterate through characters */
	while (index < line.length()) {

		/* Skip Blank Lines */
		if (isblank(line[index])) {

		/* Enter New Scope */
		} else if (line[index] == '(') {
			int temp_value = getValue(line, ++index);
			value = performOperation(value, temp_value, oper);

		/* Exit Scope */
		} else if (line[index] == ')') {
			return value;

		/* Perform operation and update value */
		} else if (isalnum(line[index])) {
			int temp_value = line[index] - '0';
			value = performOperation(value, temp_value, oper);

		/* Update operation symbol for scope and grab first element */
		} else {
			// Update operation
			oper = parseOperand(line[index++]);
			// Get first element
			while (isblank(line[index])) index++;
			if (isalnum(line[index])) value = line[index] - '0';
			else value = getValue(line, ++index);
		}
		index++;
	}
	return value;
}

// @func : readInput
// @desc : take in user input
bool readInput (string & line) {
	if (getline(cin, line)) {
		return true;
	}
	return false;
}

// @func : main
// @desc : main driver
int main(int argc, char * argv []) {
	string line; int index;
	while (readInput(line)) {
		index = 0;
		cout << getValue(line, index) << endl;
	}
	return 0;
}

