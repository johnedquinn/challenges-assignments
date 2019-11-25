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


// @func : modExp
// @desc : returns the modular exponentiation
unsigned int modExp(unsigned int a, unsigned int n, unsigned int m) {
	// Base Case
	if (n == 0) return 1 % m;

	// Recursive Case
	unsigned int r = modExp(a, n/2, m);
	r = (r * r) % m;

	// Odd Case
	if (n % 2) r = (r * a) % m;

	return r;
}

// @func : isPrime
// @desc : determines if number is prime
bool isPrime(unsigned int n) {
	for (size_t i = 2; i < n/2 + 1; i++)
		if (n % i == 0) return false;
	return true;
}

// @func : isCarmichael
// @desc : determines if number is carmichael
bool isCarmichael (unsigned int n) {
	if (isPrime(n)) return false;
	bool isCarmichael = true;
	for (size_t a = 2; a < n; a++) {
		if (a != modExp(a, n, n)) {
			isCarmichael = false;
			break;
		}
	}
	return isCarmichael;
}

// @func : main
// @desc : main driver
int main (int argc, char * argv []) {
	unsigned int n;
	while (cin >> n) {
		if (isCarmichael(n)) cout << "The number " << n << " is a Carmichael number." << endl;
		else cout << n << " is normal." << endl;
	}
	return 0;
}

