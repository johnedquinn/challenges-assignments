/*
 * File: challenge02/program.cpp
 * Author: John Ed Quinn
 * Description: This file grabs user input, adds numbers to the stack ...
 * ... and when presented with an operand, performs an operation on the two ...
 * ... numbers in the stack. The solution to all operations should result in ...
 * ... one number remaining on the stack top.
 */

/*  PREABLE */
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;

/* PROTOTYPES */
void performOperation(stack <int> & stack, char  oper);
vector <vector <string>> createMultiVector(int num);
vector <string> createVector(int num);
void printResult(vector <vector <string>> & vect);

/// Function: main
/// Description: Main driver for program.
int main() {

	string input;

	while (getline(cin, input)) {
	
		stack <int> stack;

		/* Determine if the individual substrings are digits or operands */
		string sub = "";
		for (auto it = input.begin(); it != input.end(); it++) {
			char c = *it;
			if (c == ' ' || it + 1 == input.end()) {
				/* In case operand is last */
				if (it + 1 == input.end()) {
					sub += c;
				}
				/* If number is positive or negative digit */
				if (isdigit(sub[0]) || sub.length() > 1 && isdigit(sub[1])) {
					stack.push(stoi(sub));
				} else {
					performOperation(stack, sub[0]);
				}
				/* Reset substring */
				sub = "";
			} else {
				sub += c;
			}
		}
		
		vector <vector <string>> vect = createMultiVector(stack.top());

		printResult(vect);

	}

	return 0;

}

/// Function: performOperation
/// Description: perform operation on the 2 numbers in the stack, and update stack.
void performOperation(stack <int> & stack, char oper) {
	int top = stack.top();
	stack.pop();
	switch (oper) {
		case '+':
			stack.top() = stack.top() + top;
			break;
		case '-':
			stack.top() = stack.top() - top;
			break;
		case '*':
			stack.top() = stack.top() * top;
			break;
		case '/':
			stack.top() = stack.top() / top;
			break;
		case '^':
			stack.top() = pow(stack.top(), top);
			break;
		default:
			break;
	}	
}

/// Function: createMultiVector
/// Description: Creates a two-dimensional vector. The 2nd ...
/// ... dimension will store the string representations of a digit, ...
/// ... and the 1st dimension will align all digits next to each other ...
/// ... for ease of printing. NOTE: it will create a backwards array of ...
/// ... digits, but printing it will go in reverse.
vector <vector <string>> createMultiVector(int num) {
	vector <vector <string>> vect;
	bool isNegative = false;
	/* Make sure to append negative sign at end */
	if (num < 0) {
		isNegative = true;
		num = num * -1;
	}
	/* No need to loop, just create the vector for O */
	if (num == 0) {
		vect.push_back(createVector(0));
	}
	/* Loop through digits */
	while (num > 0) {
		int digit = num % 10;
		num /= 10;
		vect.push_back(createVector(digit));
	}
	/* Append the negative */
	if (isNegative) {
		vector <string> temp = {"   ", " _ ", "   "};
		vect.push_back(temp);
	}
	return vect;
}

/// Function: createVector
/// Description: Creates a one-dimensional vector holding the ...
/// ... string representation of a single digit.
vector <string> createVector(int num) {
	vector <string> vect;
	switch (num) {
		case 0:
			vect.push_back(" _ ");
			vect.push_back("| |");
			vect.push_back("|_|");
			break;
		case 1:
			vect.push_back("   ");
			vect.push_back("  |");
			vect.push_back("  |");
			break;
		case 2:
			vect.push_back(" _ ");
			vect.push_back(" _|");
			vect.push_back("|_ ");
			break;
		case 3:
			vect.push_back(" _ ");
			vect.push_back(" _|");
			vect.push_back(" _|");
			break;
		case 4:
			vect.push_back("   ");
			vect.push_back("|_|");
			vect.push_back("  |");
			break;
		case 5:
			vect.push_back(" _ ");
			vect.push_back("|_ ");
			vect.push_back(" _|");
			break;
		case 6:
			vect.push_back(" _ ");
			vect.push_back("|_ ");
			vect.push_back("|_|");
			break;
		case 7:
			vect.push_back(" _ ");
			vect.push_back("  |");
			vect.push_back("  |");
			break;
		case 8:
			vect.push_back(" _ ");
			vect.push_back("|_|");
			vect.push_back("|_|");
			break;
		case 9:
			vect.push_back(" _ ");
			vect.push_back("|_|");
			vect.push_back(" _|");
			break;
		default:
			break;
	}
	return vect;
}

/// Function: printResult
/// Description: Moves in reverse manner across the 2-dimensional ...
/// ... array, printing the top portions of each digit, then the ...
/// ... middle portion, then the bottom portion.
void printResult(vector <vector <string>> & vect) {
	for (size_t i = 0; i < 3; i++) {
		for (auto v = vect.end() - 1; v != vect.begin() - 1; v--) {
			cout << (*v)[i];;
		}
		cout << endl;
	}
}
