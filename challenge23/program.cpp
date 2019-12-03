/*
 * File: program.cpp
 * Author: John Ed Quinn
*/

/* PREAMBLE */
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <set>
using namespace std;

// @struct : BigInt
// @desc   : big damn integer
struct BigInt {
	vector <int> digits;

	// @func : BigInt
	// @desc : default constructor
	BigInt () {}

	// @func : BigInt
	// @desc : constructor using number
	BigInt (int init_num) {
		int i = 0;
		while (init_num > 0) {
			digits.push_back(init_num % 10);
			init_num = init_num/10;
		}
	}

	// @func : +
	// @desc : add BigInts
	BigInt operator + (BigInt a) {
		BigInt result;
		int num = 0;
		int carry = 0;
		int i = 0, a_i = 0;

		// Get all digits
		while (a_i < a.digits.size() && i < digits.size()) {
			num = digits[i] + a.digits[a_i] + carry;
			if (num >= 10) {
				num = num - 10;
				carry = 1;
			}
			result.digits.push_back(num);
			i++; a_i++;
		}

		// Get remaining digits
		while (a_i < a.digits.size()) {
			result.digits.push_back(a.digits[a_i] + carry);
			carry = 0;
			a_i++;
		}

		// Get remaining digits
		while (i < digits.size()) {
			result.digits.push_back(digits[i] + carry);
			carry = 0;
			i++;
		}
		
		// Make sure carry is done
		if (carry) result.digits.push_back(carry);

		return result;
	}
	
	// @func : print
	// @desc : print the BigInt
	void operator = (BigInt a) {
		digits.clear();
		digits = a.digits;
	}

	// @func : print
	// @desc : print the BigInt
	void print () {
		for (auto it = digits.rbegin(); it < digits.rend(); it++) {
			cout << *it;
		}
	}

};

// @func : *
// @desc : multiplication
BigInt operator * (int lhs, BigInt rhs) {
	BigInt result;
	for (auto e : rhs.digits)
		result.digits.push_back(e *= lhs);
	return result;
}

// @func : sumOfDigits
// @desc : returns the sum of the digits in a string
unsigned long int sumOfDigits (string & s) {
	int total = 0;
	for (auto & c : s) {
		total += (c - '0');
	}
	return total;
}

// @func : getFormations
// @desc : finds the number of possible permutations of 1/4 in string
int getPermutations (string & s) {
	unsigned long int total = 0;
	int perms = 1;
	// Get number of 1's
	for (auto & c : s)
		if (c == '1') total++;

	// Perform factorial
	for (int i = 1; i <= total; i++)
		perms *= i;

	return (total > 0) ? perms : 0;
}

// @func : findFormations
// @desc : finds the total number of formations using memoization & permutations
BigInt findFormations (unordered_map <int, BigInt> & map, int n, string & s) {
	BigInt total;
	unsigned int sum = sumOfDigits(s);

	/* Make sure to not go over */
	if (sum > n) return 0;

	/* Base Case */
	if (sum == n) {
		return 1 + getPermutations(s);
	}

	/* Memoize */
	if (map.find(n-sum) != map.end()) {
		if (s.back() == '1') {
			return 2 * map[n-sum];
		} else {
			return map[n-sum];
		}
	}

	/* Recursive Permutation Case */
	for (unsigned int i = 1; i < 4; i++) {
		s.push_back(i + '0');
		BigInt formations = findFormations(map, n, s);
		total = total + formations;
		s.pop_back();
	}

	/* Insert for Memoization */
	map[n - sum] = total;

	return total;
}

// @func : main
// @desc : X
int main (int argc, char * argv []) {

	int n; string answer;
	unordered_map <int, BigInt> map;
	while (cin >> n) {
		BigInt solution = findFormations(map, n, answer);
		solution.print(); cout << endl;
	}

	return 0;
}

