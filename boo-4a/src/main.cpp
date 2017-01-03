// Jason Booth   Project 4a   boo-4a
// This project was created on a Linux Ubuntu 14.04 System
// This file calls the board class and tests its functionality

#include <iostream>  // For printing
#include "board.h"  // For board class
#include <cstdlib>  // Included for exit(1)

using namespace std;

int main()
{
   ifstream fin;  // Input stream

   // Read the sample grid from the file.
   string fileName = "boards/sudoku1.txt";

   // Try to open file
   fin.open(fileName.c_str());
   if (!fin)  // Can't open file
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try  // Try the following
   {
      board b1(squareSize);  // Create a Sudoku board

      // While the terminating 'Z' character has not been reached
      while (fin && fin.peek() != 'Z')
      {
		 b1.initialize(fin);  // Initialize
		 b1.print();  // Print 
		 b1.printConflicts();  // Print Conflicts
         if(b1.isSolved())  // Is the board solved?
            cout << "Solved\n\n";
         else
            cout << "Not solved\n\n";
      }
   }
   catch  (indexRangeError &ex)
   {
      // Catch and print errors
      cout << ex.what() << endl;
      exit(1);
   }

   return 0;
   
}
 
