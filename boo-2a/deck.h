// Jason Booth   project 2a   boo-2a
// This file declares the deck class

#include <iostream>  // For printing
#include "card.h"  // For card class
#include "node.h"  // For node class

#define DECK_SIZE 52  // Size of deck

using namespace std;

class deck {
    public:
    node* head;  // Stores the first card
    node* current;  // The "current element in the linked list"
    deck();  // Constructor
    ~deck();  // Destructor
    void moveCurrent(const int&);  // Move current to specified position
    friend ostream& operator << (ostream&, deck&);  // Overloaded print
};
