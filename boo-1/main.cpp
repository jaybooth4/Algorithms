// Jason Booth    project 1   boo-1
// This project was compiled on a linux, Ubuntu 14.04 system
// This file creates an object of the mastermind class and starts the game

#include <iostream>  // For cerr
#include "mastermind.h"  // Creates a mastermind object
#include "d_except.h"  // Uses error handling

using namespace std;

int main() {
    mastermind game;  // Create mastermind object

    // Error handle a bad user input
    try {
    game.playGame();  // Play game
    }

    // Catch a rangeError
    catch (const rangeError& re){
    	cerr << re.what() << endl;  // Output message
    }

    return 0;
}
