// Jason Booth   project 2b   boo-2b
// This file declares the deck class

#include <iostream>  // For printing
#include "card.h"  // For card class
#include "node.h"  // For node class
#include "d_except.h"  // For exception handling

#define DECK_SIZE 52  // Size of deck

using namespace std;

// This class stores a deck of cards and has functionality to 
// Shuffle, deal, and replace for the Flip game
class deck {
    public:
    node* head;  // Stores the first card
    node* current;  // The "current element in the linked list"
    deck();  // Constructor
    deck(deck&);  // Copy constructor
    ~deck();  // Destructor
    void moveCurrent(const int&);  // Move current to specified position
    card deal();  // Returns top card
    void replace(const card&);  // Replaces card to bottom of deck
    void shuffle();  // Mixes up card positions
    friend ostream& operator << (ostream&, deck&);  // Overloaded print
};

void playFlip();  // Global function to play game
