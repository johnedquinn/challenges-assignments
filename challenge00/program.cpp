/*
 * File: program.cpp
 * Author: John Ed Quinn
 *
 */

#include <iostream>
#include <string>

using namespace std;


/// Function: isTidy
/// Description: Determines if a number is tidy.
/// Time Complexity: O(m) if m is the number of digits in input
/// Space Complexity: O(1)
bool isTidy (int input) {
	string num_string = to_string(input);
	char first = '0';
	char second = num_string[0];
	for (int i = 0; i < num_string.length(); i++) {
		if (first > second) return false;
		first = second;
		second = num_string[i];
	}
	if (first > second) return false;
	return true;
}

/// Function: findLargestTidy
/// Description: Takes the largest number and decrements ...
/// ... until a number is tidy.
/// Time Complexity: O(n) * O(m) where n is size of deck and ...
/// ... m is digits per number
/// Space Complexity: O(1)
int findLargestTidy (int deck_size) {
	for (int num = deck_size; num > 0; num--) {
		if (isTidy(num)) return num;
  }
	return -1;
}


/// Function: main
/// Description: Loops through each deck and determines ...
/// ... which is the largest tidy number in each deck.
/// Time Complexity: O(k) * O(n) * O(m) where k is number of decks, ...
/// ... n is size of deck, and m is digits per deck.
/// Space Complexity: NA
int main () {

	int num_decks;
	cin >> num_decks;

	for (int deck = 1; deck <= num_decks; deck++) {
		int deck_size;
		cin >> deck_size;
		cout << "Deck #" << deck << ": " << findLargestTidy(deck_size) << endl;
	}

	return 0;
}


