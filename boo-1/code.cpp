// Jason Booth    project 1   boo-1
// This file contains the definitions for the code class

#include "code.h"  // Header file
#include "d_random.h"  // For random functionality

// Constructor
// Assigns stored code to all zeros, vector size of codeSize

code::code() {
    codeStore = vector<int> (codeSize, 0);

}

// Constructor
// Assigns stored code to the input vector

code::code(const vector<int>& inCode) {
    codeStore = inCode;

}

// Assigns stored code to randomly generated code
// Produced (3, 0, 2, 2) for my testing

void code::init() {
    int seed = 53412351;
    randomNumber r(seed);  // Create randomNumber object

    // Store random numbers from 0-5 in codeStore
    for (int i = 0; i < codeSize; i++) {
        codeStore.at(i) = r.random(6);    
    }

}

// Checks the number of matches in correct position comparing codeStore and 
// another code guess

int code::checkCorrect(const code& guess) const {
    int correct = 0;

    // If same element in same position increment correct
    for (int i=0; i < codeSize; i++) {
        if (codeStore.at(i) == guess.codeStore.at(i)) {
            correct++;
        }
    }

    return correct;

}

// Checks the number of matches in incorrect position comparing codeStore and
// another code guess

int code::checkIncorrect(const code& guess) const {
    int inCorrect = 0;
    vector<int> temp = codeStore;  // Temporary vector used for comparisons
    int incorrect = 0;
    
    // For each element in guess, for each element in temp check if same value
    // If same value, erase from temp so that it is not 
    // Counted twice.
    for (int i = 0; i < codeSize; i++) {
        for (int j = 0; j < temp.size(); j++) {
            if (guess.codeStore.at(i) == temp.at(j)) {
                incorrect++;
                temp.erase(temp.begin()+j);  // Erase element
            }
        }
    }

    // Above found all matches regardless of if the same position
    // Get rid of same position same value cases
    incorrect = incorrect - checkCorrect(guess);

    return incorrect;

}

// Prints the code to the user

void code::print() const {
    cout << "The code is: ";

    // For each element of the code
    for(int i = 0; i < codeSize; i++)
        cout << codeStore.at(i) << " ";

    cout << "\n";

}
