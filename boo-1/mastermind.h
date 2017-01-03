// Jason Booth    project 1   boo-1
// This file contains the declaration of the mastermind class

#include <iostream>  // For mastermind.cpp
#include "code.h"  // Because of reference to code class
#include "response.h"  // Becuase of reference to response class
#include "d_except.h"  // For exception handling

#define guessesToWin 10  // To set # guesses parameter

using namespace std;

// Class implements the user interface and game logistics

class mastermind {
    private:
    code actualCode;  // Stores the code the user is guessing for the game
    public:
    mastermind();  // Constructor
    code humanGuess() const;  // Takes in a guess from the user
    response getResponse(const code&) const;  // Generates a response
    bool isSolved(const response&) const;  // Stops game if code solved
    void print() const;  // Prints code
    void playGame() const;  // Controls game flow
};
