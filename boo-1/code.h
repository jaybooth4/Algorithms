// Jason Booth    project 1   boo-1
// This file contains the declaration of the code class

#include <iostream>  // For code definitions using cin and cout
#include <vector>  // Include vector functionality

#define codeSize 4  // Number of elements in the code

using namespace std;

// Class stores a code and implements functionality to compare to another code

class code {
    protected:
    vector<int> codeStore;  // Stores value for code
    public:
    code();  // Constructor
    code(const vector<int>& inCode);  // Constructor given vector
    void init();  // Assigns random values for the code
    int checkCorrect(const code& guess) const;  // Checks # correct
    int checkIncorrect(const code& guess) const;  // Checks # incorrect
    void print() const;  // Prints the stored code to the user
};
