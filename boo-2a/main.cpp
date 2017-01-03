// Jason Booth   project 2a   boo-2a
// This project was created on a Linux Ubuntu 14.04 System
// This file creates an object of the deck class and prints it out

#include <iostream>  // For printing
#include "deck.h"  // For deck class
#include "card.h"  // For card class
#include "d_except.h"  // For error handling

using namespace std;

int main () {
	try {
		deck deck1 = deck();  // Declare a deck object with no input arguments
		cout << deck1 << endl;  // Print it out
	}
    catch (const rangeError& re){
        cerr << re.what() << endl;  // Output message
    }
    // Should be no errors because there is no user input
    return 0;
}
