// Jason Booth   Project 4b   boo-4b
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
   string fileName = "boards/sudoku.txt";

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

      vector<int> recursions;  // Stores number of recusions for each run

      // While the terminating 'Z' character has not been reached
      while (fin && fin.peek() != 'Z')
      {
		 b1.initialize(fin);  // Initialize
		 b1.print();  // Print 
		 b1.printConflicts();  // Print Conflicts
		 int numRecs = 0;  // Number of recursions
         if(b1.assignNums(numRecs)) { // Is the board solved?
         	b1.print();  // Print
     		cout << "Number of Recursions: " << numRecs << endl << endl;
         	recursions.push_back(numRecs);  // Add number to vector
         }
         else
            cout << "Not solvable\n\n";  // Unsolvable board
      }

      int total = 0;  // Total recursions
      for (int i = 0; i < recursions.size(); i++)
    	  total += recursions[i];  // Sum
      float average = (float) (total / recursions.size());  // Calculate average
      cout << "Average number of iterations: " << average << endl << endl;  // Print av
   }
   catch  (indexRangeError &ex)
   {
      // Catch and print errors
      cerr << ex.what() << endl;
      exit(1);
   }

   return 0;
   
}
 
