// Jason Booth    project 1   boo-1
// This file contains the definitions for the mastermind class

#include "mastermind.h"  // Header file

// Constructor, calls default constructor then init() to initialize code

mastermind::mastermind() {
    actualCode = code();
    actualCode.init();  // Random code
}

// Takes in a guess and converts it to a code object

code mastermind::humanGuess() const {
    vector<int> guess;
    int number = 0;

    // For numbers in code, take in an input using error handling
    for ( int i = 0; i < codeSize; i++ ) {
       number = 0;
       cout << "Number " << i+1 << ": ";  // Number _:
       cin >> number;

       // If input is not a number
       if(cin.fail()) 
           throw rangeError(
           "ERROR: Guesss should be of type int");

       // If input is not in the appropriate range
       if (!((0 <= number) && (number <= 5))) {
        throw rangeError(
	       "ERROR: Guess should be between 0 and 5");
       }

       // Accept and add number to guess
       guess.push_back(number);
    }  // End of for()

    // Print out entered code to user
    cout << "Your code is: ";
    for (int i = 0; i < codeSize; i++)
	   cout << guess.at(i) << " ";
    
    cout << "\n";
    code returnCode(guess);  // Create code object from guess

    return returnCode;

}

// Generates a response from comparing actualCode and guess code

response mastermind::getResponse(const code& guess) const {
    int correct = actualCode.checkCorrect(guess);  // Get number correct
    int incorrect = actualCode.checkIncorrect(guess);  // Number incorrect
    return response(correct, incorrect);  // Return response
}

// Checks to see if code has been guessed by comparing response to
// an all correct response

bool mastermind::isSolved(const response& inresponse) const {
    response done(codeSize, 0);  // Create fully correct object
      if (done.compareResponses(inresponse) == true)  // If done
        return true;
    else
        return false;

}

// Prints the code to the user

void mastermind::print() const {
    actualCode.print();

}

// Starts the game, accepts 10 guesses and stops when you win or lose

void mastermind::playGame() const {
    print();  // Print the code
    int i = 0;
    // While less than 10 guesses
    while(i < guessesToWin) {
        if(i != 0)  // If not first guess
            cout << "Guess again!\n"; 
        
        // Get and print response
        response guessResponse = getResponse(humanGuess());
        guessResponse.print();

        // Code is solved
        if (isSolved(guessResponse)) {
            cout << "You win!!! \n";
            return;
        }
        i++;
    }

    // Reached 10 guesses
    cout << "You lose!!!\n";
    
    return;
}
