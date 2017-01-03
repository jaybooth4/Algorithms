// Jason Booth    project 1   boo-1
// This file contains the declaration of the response class

#include <iostream>  // Used in .cpp

using namespace std;

// Class handles the comparing of two response objects and printing of values

class response {
    private:
    int correct;  // Same value same position
    int incorrect;  // Same value different position
    public:
    response();  // Constructor
    response(const int&, const int&);  // Constructor given values
    void setCorrect(const int&);  // Set number correct
    int getCorrect() const;  // Get number correct
    void setIncorrect(const int&);  // Set number incorrect
    int getIncorrect() const;  // Get number incorrect
    bool compareResponses(response) const;  // Compare the responses
    void print() const;  // Print response
};
