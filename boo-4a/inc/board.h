// Jason Booth   Project 4a   boo-4a
// This file declares the board class

#include <algorithm>  // Included for find function
#include <iostream>  // For printing 
#include "d_matrix.h"  // For storing grid and conflicts
#include "d_except.h"  // For exception handling
#include <fstream>  // For reading from a file

using namespace std;

typedef int valueType; // The type of the value in a cell
 
//  The number of cells in a small square
//  (usually 3).  The board has
//  squareSize^2 rows and squareSize^2
//  columns.
const int squareSize = 3;

// Number of cells in a column or row
const int boardSize = squareSize * squareSize;

// Maximum and minumum displayable values
const int minValue = 1;
const int maxValue = 9;

// Stores the Sudoku board and conflicts
class board
{
   public:
      board(int);  // Constructor, calls matrix constructors
      void initialize(ifstream &fin);  // Initializes values in board
      void clear();  // Clears the board and conflicts
      bool outOfBounds(int, int);  // Checks if the cell is within the board
      valueType getCell(int, int);  // Returns the value in the cell
      void setCell(int, int, valueType);  // Sets the cell with the given val
      void clearCell(int, int);  // Clears the given cell and updates conflict values
      // Checks if adding the number to the cell will cause a conflict
      bool isConflict(int, int, valueType);
      bool isSolved();  // Checks to see if the board has been solved
      // Overloaded print operator
      friend ostream &operator<<(ostream &ostr, const matrix<bool>&); 
      void print();  // Prints sudoku board
      void printConflicts();  // Prints conflicts (row, col, square)
   private:

      // The following matrices go from 1 to boardSize in each
      // dimension.  I.e. they are each (boardSize+1) X (boardSize+1)

      // Stores values
      matrix<valueType> value;
      
      // All conflict matricies are stored in row major order. This means that
      // In the column major matrix the each column will be stored as a row.
      // Although this may make less sense intuitively it makes more sense for
      // Quick analysis and reading of the conflict matricies.

      // Row conflicts
      matrix<bool> rowConf;

      // Col conflicts
      matrix<bool> colConf;

      // Square conflicts
      matrix<bool> squareConf;

};
