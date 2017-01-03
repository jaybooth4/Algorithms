// Jason Booth   project 2b   boo-2b
// This file declares the card class

#ifndef CARD_H  // Don't include multiple times
#define CARD_H
#include <iostream>  // For printing
#include <string>  // For string manipulation

using namespace std;

// Card stores a suit and a value associated with common cards in a deck
class card {
    private:
    string suit;  // Is one of clubs, hearts, diamonds, spades
    string value;  // Is one of 1-10, Jack, Queen, King
    public:
    card();  // Constructor
    card(const string&, const int&);  // Constructor
    card(const card&);  // Copy Constructor
    string getSuit() const;  // Returns suit
    void setSuit(const string&);  // Sets suit
    string getValue() const;  // Returns value
    void setValue(const int&);  // Sets value
    card operator = (const card&);  // Overloaded = operator
    friend ostream& operator << (ostream& ostr, const card&);  // Prints card
};
#endif // CARD_H
