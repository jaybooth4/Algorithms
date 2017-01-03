// Jason Booth   project 2b   boo-2b
// This project was created on a Linux Ubuntu 14.04 System
// This file plays the game flip

#include <iostream>  // For printing
#include "deck.h"  // For deck class
#include "card.h"  // For card class
#include "d_except.h"  // For error handling

using namespace std;

int main () {
   try {
        playFlip();	 // Try to play the game
   }
   catch (const rangeError& re){
        cerr << re.what() << endl;  // Output error message
   }
   return 0;
}
