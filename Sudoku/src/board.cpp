// Jason Booth   Project 4b   boo-4b
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

	  // If the cell is not clear return
      if(getCell(row, col) != 0)
    	  return -1;

      int numNoConf = 0;  // Number of no conflict numbers
      int returnVal = -1;  // Default return value

      // For each number 1-9
      for ( int num = 1; num <= 9; num++ ) {  // For each number
            if (!isConflict(row, col, num)) {  // If no conflict
                  numNoConf = numNoConf + 1;  // Increase number of solutions
                  if(numNoConf == numSol)  // If Correct number of solutions 
                        returnVal = num;  // Set return
                  if(numNoConf > numSol)  // If more solutions 
                	  returnVal = -1;  // Return -1
            }
      }
      return returnVal;  // Return 
}

// This function clears all indicies specified in the vector that have been 
// Changed in the recursive call
void board::clearChanges(vector<int>& indicies) {

	int row = 0;  // default values
	int col = 0;
	int index = -1;
	if (indicies.size() == 0)  // If no changes
		return;
	for (int i = 0; i < indicies.size(); i++) {  // For each index
		index = indicies[i];
		row = ((index - 1)/numRows) + 1;  // Calc row
		col = ((index - 1)%numCols) + 1;  // Calc Col
		clearCell(row, col);  // Clear the cell
	}
	indicies.clear();  // Clear vector

}

// This function acts as the recursive call for the program and assigns numbers
bool board::assignNums(int &numRec)
{
	numRec++;  // Adjust the number of recursions

	vector<int> indexChanged;  // Vector of indicies changed

	// Check if solved
	if (isSolved())
		return true;

	int row = 1;  // Default vals
	int col = 1;
	int index = 1;  // From 1-81
	int singleSol = 0;  // Calculates the only number that can go in a cell
	// If for an iteration there is a cell with a single solution
	int checkOneSol = 0;
	bool oneSols = true;

	// Places every possible cell where there is only one solution
	while(oneSols) {  // While a cell was set
		oneSols = false;  // Default value
		for (int index = 1; index <= 81; index++)
		{
			row = ((index - 1)/numRows) + 1;  // Calc row
			col = ((index - 1)%numCols) + 1;  // Calc col
			if (getCell(row, col) == 0) {  // If cell == 0 
				singleSol = numberSol(index, 1);  // Get single solution
				if(singleSol != -1) {  // If solution exists
					oneSols = true;  // There was a cell placed
					indexChanged.push_back(index);  // Add to cells changed
					setCell(row, col, singleSol);  // Set cell
				}
			}
		}
	}

	// Check if solved
	if (isSolved())
		return true;

	bool solved = false;  // The board is not solved
	index = 1;

	bool unplacable = true;  // The number is not placable

	// Place a cell if there is only 2 solutions, then any with 3 solutions... 
	// This gets to the final soltuion faster based on the probability
	// Of finding the correct answer at a row with only two possibilities
	// Rather than a larger number
	for (int i = 2; i <= 9; i++) {  // For 2 solutions up to 9
		index = 1;  // From 1-81
		while (index <= maxIndex) {  // For each index
			row = ((index - 1)/numRows) + 1;  // Calc row
			col = ((index - 1)%numCols) + 1;  // Calc col
			if (getCell(row, col) == 0) {  // If cell is 0
					if (numberSol(index, i) != -1) {  // If i soltuions
						for(int num = 1; num <= 9; num++) {  // Place number
								if(!isConflict(row, col, num)) {  // If no conf
									setCell(row, col, num);  // Set
									indexChanged.push_back(index);  // Changed
									solved = assignNums(numRec);  // Recursion!
									if (solved) // Worked, puzzle complete
										return true;
									else  // Didn't work, try next number
										clearCell(row, col);  // Clear
								}
						}  // No number works for cell, unsolvable rec. call
						clearChanges(indexChanged);  // Clear changes
						clearCell(row, col);  // Clear cell
						return false;  // return cell
					}

					// If cell is 0 and no number can be placed
					for(int num = 1; num <= 9; num++) {
						if (!isConflict(row, col, num))
							unplacable = false;
					}

					// If unplacable return from recursive call
					if (unplacable) {
						clearChanges(indexChanged);  // Clear changes
						clearCell(row, col);  // Clear cell
						unplacable = true;  // Reset unplacable
						return false;  // Return
					}
			}
			index++;  // Next index
		}
	}
    return true;  // Solved
}


// Overloaded output operator for the conflict matricies
ostream &operator<<(ostream &ostr, const matrix<bool>& m)
{
   // Print each element
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
