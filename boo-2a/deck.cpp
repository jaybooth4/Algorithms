// Jason Booth   project 2a   boo-2a
// This file defines the deck class

#include "deck.h"  // Header file

// Creates a deck with cards Ace-king, Clubs-Spades
deck::deck() {
    head = new node();  // Create new node
    current = head;  // Ajust current

    // Iterate through linked list and assign suit/value
    for (int i = 0; i < DECK_SIZE; i++) {  // While < 52
        current->next = new node();  // Allocate new node
        current->cardStore.setValue((i % 13) + 1);  // Set value 1-14: Ace-King

        // Set suit based on integer division (results in whole values)
        switch (i / 13) {
            case 0:
                current->cardStore.setSuit("Clubs");
                current = current->next;  // Adjust current
                break;
            case 1:
                current->cardStore.setSuit("Diamonds");
                current = current->next;
                break;
            case 2:
                current->cardStore.setSuit("Hearts");
                current = current->next;
                break;
            case 3:
                current->cardStore.setSuit("Spades");
                current = current->next;
                break;
        }  // Switch

    }  // for

    moveCurrent(DECK_SIZE - 1);  // Set last element's next to NULL
    current->next = NULL;
}

// Moves the current pointer to the specified position
void deck::moveCurrent(const int& position) {
    current = head;  // Start at head

    // Move through list
    for (int i = 0; i < position; i++) {
        current = current->next;
    }

}

// Destructor, de-allocate the elements of the list
deck::~deck() {
	// This will call the destructor for node, which will destruct next
	// Which will then delete its next eventually iterating through the list
	delete head;
}

// Overloaded << operator
ostream& operator << (ostream& ostr, deck& inDeck) {
        inDeck.current = inDeck.head;  // Start at beginning
        ostr << "\n";  // For formatting
        int i = 0;

        // Iterate through list
        while(inDeck.current != NULL) {
            ostr << "Card " << (i+1) << ": \n" << inDeck.current->cardStore << "\n\n";
            i++;
            inDeck.current = inDeck.current->next;
        }

        return ostr;  // So that cout can continue
    }
