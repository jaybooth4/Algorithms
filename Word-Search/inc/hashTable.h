// Jason Booth   project 3b   boo-3b
// This file implements the hash table functionality

#ifndef HASHTABLE_H  // Header guard for multiple inclusion
#define HASHTABLE_H

#include <algorithm>  // For std::swap
#include <iostream>  // For cout
#include <functional>  // For hash function
//#include <string>  // For string
#include <vector>  // For vectors
#include "d_except.h"  // For exception handling

#define slots 90001  // Sets the number of slots in the hash table

using namespace std;

// This class creates a hash table and has functionality for adding,
// Searching, and deleting elements from the table
template <typename T>
class hashTable {
public:

	// Constructor to set the hash slots to empty vectors
	hashTable() {

		// For each slot
		for(int i = 0; i < slots; i++) {
			// Size zero
			table.push_back(vector<T>(0, T()));
		}

	};

	// This function adds the item to the table
	void addItem(T& addItem) {

		// Calculate slot and add to table
		int slot = getHash(addItem);
		table[slot].push_back(addItem);

	};

	// Deletes the item from the table
	void deleteItem(T& delItem) {

		// Calculate slot
		int slot = getHash(delItem);
		int index = -1;  // Default value

		// Search given slot
		for(int i = 0; i < table[slot].size(); i++) {
			// If found, set index
			if (table[slot][i] == delItem) {
				index = i;
				break;
			}
		}

		// If not found, return
		if(index == -1)
			return;
		
		// Swap the item with the last item on the list and pop_back
		int size = table[slot].size();
		swap(table[slot][index], table[slot][size - 1]);
		table[slot].pop_back();

	};

	// Returns true if the parameter is in the list and false if not
	bool inList(T& inValue) {

		//Calculate slot
		int slot = getHash(inValue);
	
		// Search given slot
		for(int i = 0; i < table[slot].size(); i++) {
			// If found, set index
			if (table[slot][i] == inValue) {
				return true;  // Found
			}
		}
		return false;  // Not found
	};

	// Returns the hash for the given value
	int getHash(T& key) {

		// Calls the hash function on the key
		// Returns the modulus of the number of slots
		return (hashFunc(key) % slots);

	};

    // Overloaded [] operator, returns slot using array indexing
    vector<T>& operator[](const int& slot) {

            // Check row accessor less than 0
            if (slot < 0) {
                    throw rangeError("Error: Row must be greater than or equal to 0");
            }

            // Check row accessor greater than size
            if (slot >= table.size()) {
                    throw rangeError("Error: Row must less than the number of rows");
            }

            // Return vector using array indexing
            return table[slot];

    }

    // Overloaded [] operator for const table
    const vector<T>& operator[](const int& slot) const {

            // Check row accessor less than 0
            if (slot < 0) {
                    throw rangeError("Error: Row must be greater than or equal to 0");
            }

            // Check row accessor greater than size
            if (slot >= table.size()) {
                    throw rangeError("Error: Row must less than the number of rows");
            }

            // Return vector using array indexing
            return table[slot];

    }

private:
	hash<T> hashFunc;  // Hash
	vector<vector <T> > table;  // Hash Table as a vector of vectors

};

#endif  // HASHTABLE_H
