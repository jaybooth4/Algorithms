// Jason Booth   project 3b   boo-3b
// This file implements the matrix class for storing the word search

#ifndef MATRIX_H  // Header guard for multiple inclusion
#define MATRIX_H

#include <iostream>  // For printing
#include <vector>  // For vector operations
#include "d_except.h"  // For error handling

using namespace std;

// This is a templated class which will store the word search
// Because it is a template class there is no separate .cpp file
template<typename T>
class matrix {
public:

	// Constructor, sets number of rows and columns, stores default values
	matrix(int numRows = 1, int numCols = 1, const T& initVal = T()) {

		// If number of rows or columns is out of bounds throw error
		if ((numRows <= 0) || (numCols <= 0)) {
			throw rangeError("Error: Number of rows and columns must "
					"be greater than 0");
		}

		// For each row add a vector
		// Initialized to initVal, with numCols elements
		for (int i = 0; i < numRows; i++) {
			mat.push_back(vector<T>(numCols, initVal));
		}

	}

	// Overloaded [] operator, returns row using array indexing
	vector<T>& operator[](const int& row) {

		// Check row accessor less than 0
		if (row < 0) {
			throw rangeError("Error: Row must be greater than or equal to 0");
		}

		// Check row accessor greater than size
		if (row >= mat.size()) {
			throw rangeError("Error: Row must less than the number of rows");
		}

		// Return vector using array indexing
		return mat[row];

	}

	// Overloaded [] operator for const matrix
	const vector<T>& operator[](const int& row) const {

		// Check row accessor less than 0
		if (row < 0) {
			throw rangeError("Error: Row must be greater than or equal to 0");
		}

		// Check row accessor greater than size
		if (row >= mat.size()) {
			throw rangeError("Error: Row must less than the number of rows");
		}

		// Return vector using array indexing
		return mat[row];

	}

	// Returns number of rows
	int rows() const {

		return nRows;

	}

	// Returns number of columns
	int cols() const {

		return nCols;

	}

	// Resizes the matrix to the given dimensions
	void resize(const int& newRows, const int& newCols) {

		// If number of rows or columns is out of bounds throw error
		if ((newRows <= 0) || (newCols <= 0)) {
			throw rangeError("Error: Number of rows and columns must "
					"be greater than 0");
		}

		// Resize matrix to new number of rows
		mat.resize(newRows);

		// Resize matrix to new number of columns, initializing to
		// Default value if numCols is larger than nCols
		for (int i = 0; i < mat.size(); i++) {
			mat[i].resize(newCols, T());
		}

		// Assign private variables
		nRows = newRows;
		nCols = newCols;

	}

	// For printing the word search
	void print() {

		// For each element print to user
		for (int row = 0; row < nRows; row++) {
			for (int col = 0; col < nCols; col++) {
				cout << mat[row][col] << " ";  // Print formatted
			}

			cout << endl;  // New line between each row
		}

		// For
		cout << "-----------------------------\n";

	}


private:
	// Number of rows and columns
	int nRows, nCols;

	// Stores the matrix for the word search
	vector<vector<T> > mat;
};

#endif  // MATRIX_H
