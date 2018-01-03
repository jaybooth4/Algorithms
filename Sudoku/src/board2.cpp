// Jason Booth   Project 4a   boo-4a
// This file defines the board class

#include "board.h"  // Header file 

// Return the square number (1-9) of cell counting from left to right,
// top to bottom.
// Note that (int) row/squareSize and (int) col/squareSize are the x-y
// coordinates of the square that row, col is in. This is used when 
// checking the conflict matrix for a square
int squareNumber(int row, int col)
{
   return (squareSize * ((row-1)/squareSize)) + ((col-1)/squareSize) + 1;
}

// Constructor calls constructor for row, col, and square
board::board(int sqSize)
   : value(boardSize+1,boardSize+1),
	 rowConf(boardSize+1,boardSize+1),
	 colConf(boardSize+1,boardSize+1),
	 squareConf(boardSize+1,boardSize+1) {}

// Read a Sudoku board from the input file.
void board::initialize(ifstream &fin)
{

   char ch;  // Char for reading

   clear();  // Clear all matricies
   for (int i = 1; i <= boardSize; i++)
      for (int j = 1; j <= boardSize; j++)
      {
		 fin >> ch;  // Read Char

	     // If the read char is not Blank
		 if (ch != '.')
		 {
				setCell(i,j,ch-'0');  // Convert char to int
		 }
      }
}

// clear the entire board using resize function
void board::clear()
{
	// Empty the board
	value.resize(0,0);  
	rowConf.resize(0,0);
	colConf.resize(0,0);
	squareConf.resize(0,0);

	// Create a board of the appropriate size instantiated with 0s
	value.resize(boardSize+1, boardSize+1);
	rowConf.resize(boardSize+1, boardSize+1);
	colConf.resize(boardSize+1, boardSize+1);
	squareConf.resize(boardSize+1, boardSize+1);
}

// Returns true if value is out of bounds, and false if within
bool board::outOfBounds(int row, int col)
{
   if (row < 1 || row > boardSize || col < 1 || col > boardSize)
      return true;
   else
	   return false;
}

// Returns the value stored in a cell. Throws an exception
// if bad indecies are passed.
valueType board::getCell(int row, int col)
{
   // If the position is out of bounds
   if (outOfBounds(row, col))
   	   throw rangeError("bad value in getCell");
   else
	   return value[row][col];  // Return value

}

// Set cell i,j to val and update conflicts
void board::setCell(int row, int col, valueType val)
{
   if (outOfBounds(row, col)) // If out of bounds
	   throw rangeError("bad value in setCell");
   if (isConflict(row, col, val))  {  // If conflict
	   throw rangeError("value causes conflict in setCell, cannot be set");
   }
   value[row][col] = val;  // Set value
   if (val != 0) {
	   rowConf[row][val] = true;  // Set conflict values
	   colConf[col][val] = true;
	   squareConf[squareNumber(row, col)][val] = true;
   }
}

// Clears the cell and updates the conflict values. Because of the set up of 
// This program, the values will only be set if all conflicts are false.
// Therefore a clear can reasonably set conflicts to false.
void board::clearCell(int row, int col) 
{
    if (outOfBounds(row, col))  // If out of bounds
         throw rangeError("bad value in clearCell");
    if (getCell(row, col) == 0)  // If cell is already clear
    	return;
    valueType prevCell = getCell(row, col);  // Save previous value
    setCell(row, col, valueType());  // Set the value to default value
    rowConf[row][prevCell] = false;  // Set conflict values
    colConf[col][prevCell] = false;
    squareConf[squareNumber(row, col)][prevCell] = false;
}

// Determines if placing a value in the position would cause a conflict
bool board::isConflict(int row, int col, valueType val)
{
	bool rowBool = rowConf[row][val];  // Check row conflicts
	bool colBool = colConf[col][val];  // Check col conflicts
	// Check square conflicts
	bool squareBool = squareConf[squareNumber(row, col)][val];
	// Return the logical or of each bool
	return ( rowBool || colBool || squareBool ); 
}

// Checks to see if the board is solved
bool board::isSolved() 
{

	// Row conflict matrix
	for (int i = 1; i < rowConf.rows(); i++)
	{
		// For each row search for a false, meaning there is an open spot
		if(find((rowConf[i].begin()+1), rowConf[i].end(), false) != 
		(rowConf[i]).end())
			return false;
	}

	// Column conflict matrix
	for (int i = 1; i < colConf.rows(); i++)
	{
		if(find((colConf[i].begin()+1), colConf[i].end(), false) != 
		(colConf[i]).end())
			return false;
	}

	// Square conflict matrix
	for (int i = 1; i < squareConf.rows(); i++)
	{
		if(find((squareConf[i].begin()+1), squareConf[i].end(), false) != 
		(squareConf[i]).end())
			return false;
	}

	// If no falses found, it is solved
	return true;

}

// Calculates for a given cell what the numSol'th solution for the cell is.
// For instance if a 2 3 or 4 only can be placed in a cell, the 1st solution
// is 2, the second is 3, and the third is 4. If 4 is passed in for numSol,
// The function will return -1
int board::numberSol(int index, int numSol)
{


      // This provides the appropriate row for a given index
      int row = ((index-1)/numRows) + 1;

      // This provides the appropriate col for a given index
      int col = ((index-1)%numCols) + 1;

      if(getCell(row, col) != 0)
    	  return -1;

      int noConflict = 0;
      int returnVal = -1;

      // For each number 1-9
      for ( int num = 1; num <= 9; num++ ) {
            if (!isConflict(row, col, num)) {
                  noConflict = noConflict + 1;
                  if(noConflict == numSol)
                        returnVal = num;
                  if(noConflict > numSol)
                	  returnVal = -1;
            }
      }
      return returnVal;
}

void board::clearChanges(vector<int>& indicies) {

	int row = 0;
	int col = 0;
	int index = -1;
	if (indicies.size() == 0)
		return;
	for (int i = 0; i < indicies.size(); i++) {
		index = indicies[i];
		row = ((index - 1)/numRows) + 1;
		col = ((index - 1)%numCols) + 1;
		clearCell(row, col);
	}
	indicies.clear();
}


bool board::assignPos(int index, int &numRec)
{

	numRec++;  // Adjust the number of recursions

//	cout << "Num Recs: " << numRec << endl;

	bool solved = false;  // The board is not solved

	vector<int> indexChanged;

	// Check if solved
	if (isSolved())
		return true;

	int row = 0;
	int col = 0;

	// Check and set any cells with only 1 solution
	int checkOneSol = 1;  // From 1-81
	int singleSol = 0;
	while (checkOneSol <= maxIndex)
	{
		row = ((checkOneSol - 1)/numRows) + 1;
		col = ((checkOneSol - 1)%numCols) + 1;
		if (getCell(row, col) == 0) {
			singleSol = numberSol(checkOneSol, 1);
			if(singleSol != -1) {
				indexChanged.push_back(checkOneSol);
				setCell(row, col, singleSol);
			}
		}
		checkOneSol++;
	}

	// Check if solved
	if (isSolved())
		return true;

	// Recursive call, Go through each cell with more than one solution
    while (index < maxIndex) {

    	// Calculate row and col
        row = ((index-1)/numRows) + 1;
        col = ((index-1)%numCols) + 1;



        if (getCell(row, col) == 0) {

			// Find the first acceptable number to place
			for(int num = 1; num <= 9; num++) {
				if(!isConflict(row, col, num)) {
					setCell(row, col, num);
					solved = assignPos(index+1, numRec);  // Recursion!
					if (solved) // Worked, puzzle complete
						return true;
					else {
						clearChanges(indexChanged);
						clearCell(row, col);
					}
				}
			}
			clearChanges(indexChanged);
			clearCell(row, col);
			return false;
		}
		index++;
    }  // Made it all of the way through and
	if(numberSol(81, 1) != -1)
		setCell(9,9, numberSol(81, 1));
    return true;
}

// Overloaded output operator for the conflict matricies
ostream &operator<<(ostream &ostr, const matrix<bool>& m)
{
   for (int row = 1; row < m.rows(); row++)
	{
	   for (int col = 1; col < m.cols(); col++)
			ostr << m[row][col] << " ";
	   ostr << endl;
	}
   return ostr;
}

// Prints the current board formatted for user viewing
void board::print()
{
   // i iterates down rows, j across columns
   for (int i = 1; i <= boardSize; i++)
   {
	  // ------------------- ...
      if ((i-1) % squareSize == 0)
      {
         cout << " -";
		 for (int j = 1; j <= boardSize; j++)
			cout << "---";
		 cout << "-";
		 cout << endl;
      }
	  // | number number number | ...
      for (int j = 1; j <= boardSize; j++)
      {
		 if ((j-1) % squareSize == 0)
			cout << "|";
		 if (!outOfBounds(i,j))
			cout << " " << getCell(i,j) << " ";
		 else
			cout << "   ";
      }
      cout << "|";
      cout << endl;
   }

   // Bottom line ------------- ...
   cout << " -";
   for (int j = 1; j <= boardSize; j++)
      cout << "---";
   cout << "-";
   cout << endl << endl;
}

// Print the conflict matricies
void board::printConflicts() 
{
	cout << rowConf << endl;
	cout << colConf << endl;
	cout << squareConf << endl;
}
