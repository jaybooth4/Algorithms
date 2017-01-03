// Jason Booth   project 3a   boo-3a
// This file declares the wordList class for creating, sorting, and
// searching the dictionary

#ifndef WORDLIST_H  // Header guard for multiple inclusion
#define WORDLIST_H

#include <algorithm>
#include <iostream>  // For printing
#include <fstream>  // For reading from file
#include <vector>  // For vector manipulation
#include <string>  // For string manipulation
#include "d_except.h"  // Exception handling
#define ENDWORD "zzzzzzzzzzz"  // Define a maximum string value for merge sort

using namespace std;

// This class reads a dictionary into a vector of strings and performs
// Sorting and searching on the list
class wordList {
public:
	void readWords(const string&);  // Reads words in to vector of strings
	int size(); // Returns the size of the dictionary
	void sortInsert();  // Insert sort
	void sortQuick(const int&, const int&);  // Quick sort
	int quickAux(const int&, const int&); 	// Auxillary func
	void sortMerge(const int&, const int&);  // Merge sort
	void mergeAux(const int&, const int&, const int&); // Auxillary func
	int binarySearch(const string&);  // Binary search
	// Auxillary func
	int binarySearchAux(const string&, const int&, const int&);
	// Overloaded << operator
	friend ostream& operator << (ostream& ostr, const wordList&);
	// Overloaded [] operator
	string& operator[](const int& index);
	// Overloaded [] operator for const
	const string& operator[](const int& index) const;
private:
	vector<string> words;
};
#endif  // WORDLIST_H
