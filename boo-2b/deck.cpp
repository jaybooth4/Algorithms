// Jason Booth   project 2b   boo-2b
// This file defines the deck class and the playFlip global function to play
// The flip game 

#include "deck.h"  // Header file
#include "d_random.h"  // For random functionality

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
        }  // switch

    }  // for

    moveCurrent(DECK_SIZE - 1);  // Set last element's next to NULL
    current->next = NULL;
}

// Moves the current pointer to the specified position
void deck::moveCurrent(const int& position) {
    current = head;  // Start at head

    // Check for bounds, throw error if larger than size of deck
	if (position > DECK_SIZE) {
		throw rangeError("Error: Invalid value passed to setSuit()");
	}
    
    // Move through list
    for (int i = 0; i < position; i++) {
        current = current->next;
    }

}

// Copy constructor
deck::deck(deck& inDeck) {
    head = inDeck.head;  // Copy head
    inDeck.current = inDeck.head;  // Move inDeck current to head

    // Assign each node to inDeck node
    for (int i = 0; i < DECK_SIZE; i++) {
        current = inDeck.current;  // Copy node
        inDeck.current = inDeck.current->next;  // Move inDeck current
        current = current->next;  // Move current
    }  // for

}

// Destructor, de-allocate the elements of the list
deck::~deck() {
    current = head;  

    // Iterate through list and delete each node
    for (int i = 0; i < DECK_SIZE; i++) {
        head = current->next;  // Adjust head
        delete current;  // Delete node
	    current = head;  // Adjust current
    }  // for 

}

// Returns the top card of the deck, removes the card
card deck::deal() {
    current = head;  // Adjust current
    card temp = head->cardStore;  // Create temp card
    head = current->next;  // Move head
    delete current;  // Delete node
    return temp;  // Return card
}

// Replaces input card to the bottom of the deck
void deck::replace(const card& inCard) {

    // Current goes to the end of the list
    while(current->next != NULL) {
        current = current->next;
    }  // while

    current->next = new node();  // Create new node
    current = current->next;  // Adjust current
    current->cardStore = inCard;  // Ajust stored card
}

// Randomly shuffles the cards in the deck to other positions
void deck::shuffle() {
    int cardPosition1, cardPosition2 = 0;  // Positions that will be exchanged
    int seed = 12342432;  // For randomNumber object
    randomNumber r(seed);  // Create object
    node* switchNode = NULL;  // Node to be switched
    card switchCard = card();  // Card to be switched 
    
    // Make a card switch for two random nodes
    for (int i = 0; i < DECK_SIZE; i++) {
        cardPosition1 = r.random(DECK_SIZE);  // Random number
        cardPosition2 = r.random(DECK_SIZE);  // 0-52
        moveCurrent(cardPosition1);  // Move current
        switchNode = current;  // Assign switch node
        moveCurrent(cardPosition2);  // Move current to new card
        switchCard = current->cardStore;  // Get card
        current->cardStore = switchNode->cardStore;  // Switch cards
        switchNode->cardStore = switchCard;
    }  // for

}

// Overloaded << operator
ostream& operator << (ostream& ostr, deck& inDeck) {
        inDeck.current = inDeck.head;  // Start at beginning
        ostr << "\n";  // For formatting
        int i = 0;

        // Iterate through list
        while(inDeck.current != NULL) {
            ostr << "Card " << (i+1) << ": \n" << 
            inDeck.current->cardStore << "\n\n";  // Calls overloaded card <<
            i++;
            inDeck.current = inDeck.current->next;
        }

        return ostr;  // So that cout can continue
    }

// Implements the functionality to play the game Flip
void playFlip() {
   deck gameDeck;  // Create deck using defined constructor
   gameDeck.shuffle();  // Shuffle 3 times
   gameDeck.shuffle();
   gameDeck.shuffle();
   card printCard = card();  // Card to be printed
   int score = 0;  // User's score
   char choice = 'y';  // Initial state of user's choice to continue or quit
   cout << "Press 'y' to choose a card. Press 'n' to end the game" 
   << endl;  // How to play

   // Repeat forever
   while (1) {
       // Process user input, check if 'y' or 'n'
       while (1) {
            cin >> choice;  // Read in value
            if (choice == 'n') {  // End game
                cout << "Final score is: " << score << endl;  // Print score
                return;  // End game
            } else if (choice == 'y')  // Contine with another iteration
                break;
            cout << "I did not understand your input. " 
            "Press 'y' to choose another card. Press 'n' to end the game" 
            << endl;  // Print error message
        }  // while inner

        printCard = gameDeck.deal();  // Call deal to return top card
        gameDeck.replace(printCard);  // Replace card at the bottom of the deck
        cout << printCard;  // Print card
        if (printCard.getValue() == "Ace")  // Ace = +10
        score += 10;
        else if(printCard.getValue() == "Jack" || 
        printCard.getValue() == "Queen" || printCard.getValue() == "King")
            score += 5;  // Face card = +5
        else if(printCard.getValue() == "7")
        score = score/2;  // 7 divides score in half
        else if(printCard.getValue() == "2" || printCard.getValue() == "3" ||
         printCard.getValue() == "4" || printCard.getValue() == "5" ||
         printCard.getValue() == "6")
        score = 0;  // 2, 3, 4, 5, 6 set score back to 0
        if(printCard.getSuit() == "Hearts")
        score += 1;  // Hearts increases score by 1
        cout << "Score is: " << score << endl;  // Prints current score
        cout << "Continue?" << endl;
   }  // while outer
   
}
