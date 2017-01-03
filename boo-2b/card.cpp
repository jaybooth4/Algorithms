// Jason Booth   project 2b   boo-2b
// This file defines the card class

#include "card.h"  // Header
#include "d_except.h"  // For exception handling

// Constructor
card::card() {
	suit = "";  // Default values are ""
	value = "";
}

// Constructor sets values of suit and value
card::card(const string& inSuit, const int& inValue) {
	setSuit(inSuit);  // Calls member functions
	setValue(inValue);
}

// Copy Constructor, sets suit and value
card::card(const card& inCard):
suit(inCard.getSuit()), value(inCard.getValue())
{}

// Returns suit
string card::getSuit() const {
	return suit;
}

// Sets suit, checks boundary condition with exception handling
void card::setSuit(const string& inSuit) {

	// If input is invalid, throw error 
	if (inSuit != "Spades" && inSuit != "Hearts" && inSuit
			!= "Diamonds" && inSuit != "Clubs") {
		throw rangeError("Error: Invalid suit name passed to setSuit()");
	}
	else {
		suit = inSuit;  // Assign suit
	}
}

// Returns value
string card::getValue() const {
	return value;
}

// Sets value, checks boundary condition with exception handling
void card::setValue(const int& inValue) {

	// Exception handling
	if (!(2 <= inValue <= 14)) {
		throw rangeError("Error: Invalid value passed to setSuit()");
	}

	// Converts number to the appropriate sting value
	switch(inValue) {
	case 1: {
		value = "Ace";  // Set Ace
		break;
	}
	case 11: {
		value = "Jack";  // Set Jack
		break;
	}
	case 12: {
		value = "Queen";  // Set Queen
		break;
	}
	case 13: {
		value = "King";  // Set King
		break;
	}
	default: {
		value = to_string(inValue);  // Set "Number"
		break;
	}
	}
}

// Overloaded = operator 
card card::operator = (const card& inCard) {
	suit = inCard.getSuit();  // Assign suit and value
	value = inCard.getValue();
	return *this;  // Return object
} 

// Overloaded << operator
ostream& operator << (ostream& ostr, const card& inCard) {
	// Use member functions to access member variables
	ostr << "Suit: " << inCard.getSuit() << "\nValue: " << inCard.getValue() << endl;
	return ostr;  // Return stream
}
