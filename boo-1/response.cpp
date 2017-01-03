// Jason Booth    project 1   boo-1
// This file contains the definitions for the response class

#include "response.h"  // Header file

// Constructor, correct and incorrect initialized to 0

response::response() {
        correct = 0;
        incorrect = 0;

}

// Constructor, correct and incorrect initialized to inputs

response::response(const int& numCorrect, const int& numIncorrect) {
        correct = numCorrect;
        incorrect = numIncorrect;

}

// Set the value of correct to input int

void response::setCorrect(const int& numCorrect) {
    correct = numCorrect;

}

// Get the value of correct

int response::getCorrect() const {
    return correct;

}

// Set the value of incorrect to input int

void response::setIncorrect(const int& numIncorrect) {
    incorrect = numIncorrect;

}

// Get the value of incorrect

int response::getIncorrect() const {
    return incorrect;

}

// Compare input respose to private variable
// Return true if they are the same, false if they are different

bool response::compareResponses(response inResponse) const {
    if ((correct == inResponse.getCorrect()) && (incorrect == inResponse.getIncorrect()))
        return true;
    else
        return false;

}

// Print the response to the user

void response::print() const {
    cout << "Number Correct:\n" << correct << "\n";
    cout << "Number Incorrect:\n" << incorrect << "\n";

}
