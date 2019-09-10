/*
 * File: challenge03/program.cpp
 * Author: John E Quinn
*/

/* Preamble */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* Prototypes */
bool canFit(vector<int> vect, int numFlowers, int optimalLength);


/// Function: main
/// Description: Get in user input and perform binary search to ...
/// ... determine the most optimal length between pots
int main()
{

    int numAvailablePots;
    while (cin >> numAvailablePots)
    {

        int numFlowers;
        cin >> numFlowers;

        vector<int> vect;

        /* Insert values into vector */
        for (size_t i = 0; i < numAvailablePots; i++)
        {
            int temp;
            cin >> temp;
            vect.push_back(temp);
        }

        /* Sort vector */
        sort(vect.begin(), vect.end());

        /* Binary search to determine the highest optimal length */
        int low = 0;
        int high = *(vect.end() - 1);
        int highest = 0;
        while (low <= high)
        {
            int length = (high - low) / 2;
            int mid = low + length;
            if (canFit(vect, numFlowers, mid))
            {
                highest = (highest < mid) ? mid : highest;
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        cout << highest << endl;
    }

    return 0;
}

/// Function: canFit
/// Description: Determines if flowers can be placed every 'optimalLength' or more pots.
bool canFit(vector<int> vect, int numFlowers, int optimalLength)
{

    /* Place flower in first available pot */
    int lastInput = vect[0];
    numFlowers--;

    /* Loop through available pots and insert accordingly */
    for (int i = 1; i < vect.size(); i++)
    {
        while (i < vect.size() && vect[i] - lastInput - 1 < optimalLength)
            i++;
        if (i < vect.size())
        {
            lastInput = vect[i];
            numFlowers--;
        }
    }
    return numFlowers <= 0;
}