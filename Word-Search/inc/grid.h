// Jason Booth   project 3b   boo-3b
// This file implements the grid class for reading in the word search

#ifndef GRID_H  // Header guard for multiple inclusion
#define GRID_H

#include <fstream>  // For reading from file
#include "matrix.h"  // For matrix class
#include "d_except.h"  // For error handling

using namespace std;

// "grid" is a templated class to read in the word search
template<typename T>
class grid {
public:

	// Reads the specified file into a matrix of the file specified size
	void readFile(const string& fileLocation) {

		ifstream fin;  // Input file stream
		fin.open(fileLocation.c_str());  // Attempt to open stream

		// Error handling, if file cannot be opened throw error
		if (!fin) {
			throw fileOpenError(fileLocation);  // Name of file
		}

		// Read in number of rows and columns
		int rows, cols;
		fin >> rows;
		fin >> cols;

		// Error handling done in matrix class
		mat.resize(rows, cols);

		// Read in and assign values
		// For each row, for each column
		T readIn;
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				fin >> readIn;  // Read in the value
				mat[row][col] = readIn;  // Assign value to position
			}
		}

		fin.close();  // Close the file

	}

	// Returns number of rows
	int numRows() const {

		// Calls matrix class function
		return mat.rows();

	}

	// Returns number of columns
	int numCols() const {

		// Calls matrix class function
		return mat.cols();

	}

	// Overloaded [] operator
	vector<T>& operator[](const int& row) {

		// Calls matrix class function
		return mat[row];
	}

	// Overloaded [] operator for const
	const vector<T>& operator[](const int& row) const {

		// Calls matrix class function
		return mat[row];

	}

	// Prints matrix
	void print() {

		mat.print();  // Calls matrix function

	}

private:

	// Stores matrix
	matrix<T> mat;

};

#endif  // GRID_H
