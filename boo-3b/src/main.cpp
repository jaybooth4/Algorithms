// Jason Booth   project 3b   boo-3b
// This project was created on a Linux Ubuntu 14.04 System
// This file implements the main function and several global functions

#include <iostream>  // For cout
#include <algorithm>  // For std::reverse
#include <time.h>  // For timing
#include "heap.h"  // For heap sort
#include "hashTable.h"  // For hash table
#include "wordList.h"  // For wordlist
#include "grid.h"  // For grid class
#include "matrix.h"  // For matrix class
#include "d_except.h"  // For exception handling

using namespace std;

enum direction { vertical, horizontal, diagonalRight, diagonalLeft };

// This function searches the dictionary for all legal values within the vector
// It searches each combination forward and reversed
template <typename T1, typename T2>
void searchDict(T2& dictionary, const vector<T1>& inVector) {

	int size = inVector.size()/2;  // Size of the vector

	// For each element
	for (int elem = 0; elem < size; elem++) {
		// For each possible size of the word
		for (int wordSize = 5; wordSize < size; wordSize++) {

			// Create string from vector at starting and ending indicies
			string key(inVector.begin() + elem,
					inVector.begin() + elem + wordSize);

			// If not -1, print word
			if (dictionary.inList(key))
				cout << key << endl;

			reverse(key.begin(), key.end());  // Reverse the string

			if (dictionary.inList(key))
				cout << key << endl;

		}

	}

}

/*
   This function returns a vector with all of the characters in the specified
   search direction. It uses an enum at the top to specify how the indicies
   will change when searching in a given direction. The starting positions and
   absolute value are used because some of the delta values are negative, and
   in order for the modulo function to work properly, the row and column values
   should not go negative.
*/
template <typename T>
vector<T> searchIndex(grid<T>& wordSearch, const int& indexRow,
		              const int& indexCol, const direction& dir) {

	// Vector of chars to be searched for words
	vector<T> returnSearch;

	// Delta corresponds to how much the row and column will change each loop
	int deltaRow = 0;
	int deltaCol = 0;

	// Sets the delta and circle values for the specified search direction
	switch(dir) {
		case vertical: {  // Search vertically
			deltaRow = 0;  // Don't change row
			deltaCol = 1;  // Change col right
			break;
		}
		case horizontal: {  // Search horizontally
			deltaRow = 1;  // Change row down
			deltaCol = 0;  // Don't change column
			break;
		}
		case diagonalRight: {  // Search diagonally right
			deltaRow = 1;  // Change row by down
			deltaCol = -1;  // Change column left
			break;
		}
		case diagonalLeft: {
			deltaRow = -1;  // Change row up
			deltaCol = -1;  // Change column left
			break;
		}
	}

	//	Starting positions, add numRows/Cols so that modulo wont go negative
	int row = indexRow + wordSearch.numRows();
	int col = indexCol + wordSearch.numCols();

	// Do while loop is used to add the char at the given
	// index first, then search in the given direction.
	// Continue until reaching back to original position
	do{

		// Add char to vector
		returnSearch.push_back(wordSearch[abs(row % wordSearch.numRows())]
										  [abs(col % wordSearch.numCols())]);
		row = row + deltaRow;// Adjust row
		col = col + deltaCol;// Adjust col
	} while ((abs(row % wordSearch.numRows()) != indexRow) ||
			(abs(col % wordSearch.numCols()) != indexCol));

	// Make another copy of the vector so that looping can be performed in
	// searchDict function
	int size = returnSearch.size();
	for (int elem = 0; elem < size; elem++)
		returnSearch.push_back(returnSearch[elem]);

	return returnSearch;  // Represents all char values in a search direction

}


/*
   This function finds all matches in the dictionary for the given grid
   The algorithm works by starting at the top left and traversing down
   diagonally searching vertically and horizontally at each position.
   To capture all possible values the search starts again at the top and
   travels down the left most column, search diagonally in both directions.
   Within each while loop the searchDict function is called on the dictionary
   and the vector of chars returned by the searchIndex function.
*/
template <typename T1, typename T2>
void findMatches(grid<T1>& wordSearch, T2& dictionary) {

	int indexRow = 0;
	int indexCol = 0;
	// Traverse down and over diagonally, search vertically and horizontally
	while((indexRow < wordSearch.numRows()) &&
			(indexCol < wordSearch.numCols())) {

		// Search vertically
		searchDict<T1, T2>(dictionary, searchIndex<T1>(wordSearch, indexRow,
												 indexCol, vertical));

		// Search horizontally
		searchDict<T1, T2>(dictionary, searchIndex<T1>(wordSearch, indexRow,
												 indexCol, horizontal));
		indexRow++;
		indexCol++;  // Change index
	}

	// Reseat indices
	indexRow = 0;
	indexCol = 0;
	// Traverse down the first column, search diagonally in both directions
	while(indexCol < wordSearch.numCols()) {

		// Search diagonally left
		searchDict<T1, T2>(dictionary, searchIndex<T1>(wordSearch, indexRow,
												 indexCol, diagonalLeft));

		// Search Diagonally right
		searchDict<T1, T2>(dictionary, searchIndex<T1>(wordSearch, indexRow,
												 indexCol, diagonalRight));
		indexCol++;  // Change index
	}

	return;

}

// This function prints the time values for the run
void printTime( const clock_t& startTime, const clock_t& startSort,
				const clock_t& startFind, const clock_t& endTime) {

	int diff;  // Difference between times
	float seconds;  // Difference in seconds

	cout << "-------------------------------" << endl;  // For display

	// Calculate sorting time
	diff = startFind - startSort;
    seconds = (float) diff / CLOCKS_PER_SEC;
    cout << "Time for sorting: " << seconds << endl;

    // Calculate searching time
	diff = endTime - startFind;
    seconds = (float) diff / CLOCKS_PER_SEC;
    cout << "Time for searching: " << seconds << endl;

    // Calculate total time (including read in of grid)
	diff = endTime-startTime;
    seconds = (float) diff / CLOCKS_PER_SEC;
    cout << "Total time for program: " << seconds << endl;

	cout << "-------------------------------" << endl;  // For display

}

// This function prints the sort and search methods
void printMethods (const int& sortType, const int& searchType) {

	string sortMethod, searchMethod;
	// Switch statement for user display of sort and search methods
	// Sort type
	switch (sortType) {
		case 1: {
			sortMethod = "Insert";
			break;
		}
		case 2: {
			sortMethod = "Quick";
			break;
		}
		case 3: {
			sortMethod = "Merge";
			break;
		}
		case 4: {
			sortMethod = "Heap";
			break;
		}
	}

	// Search type
	switch (searchType) {
		case 1: {
			searchMethod = "Binary";
			break;
		}
		case 2: {
			searchMethod = "Hash Table";
			break;
		}
	}

	// Read in wordSearch
	cout << "\nPlease input file name for " << sortMethod << " Sort and "
			<< searchMethod << " Search: \n";
}

// This function reads the specified file into a grid and
// Reads in the dictionary, sorting it based on the specified method
template <typename T>
void search(const int& sortType, const int& searchType) {

	// Clock times for sorting, searching, and total
	clock_t startTime, startSort, startFind, endTime;
	string sortMethod, searchMethod;  // String for clear user display
	string fileLocation;  // File location
	grid<T> wordSearch = grid<T> ();  // Create grid object

	printMethods(sortType, searchType);

	// Be sure to use grid/filename format
	cin >> fileLocation;  // Error handling in wordSearch class
	startTime = clock();  // Assign start time (After user input)
	wordSearch.readFile(fileLocation);  // Read file

	// Create wordList object
	wordList wordsList;
	wordsList.readWords("dictionary.txt");  // Dictionary of words

	// Create hash table object
	hashTable<string> hashTab;

	// Read in elements from dictionary
	for (int i = 0; i < wordsList.size(); i++) {
		hashTab.addItem(wordsList[i]);
	}

	// Specify which type of sorting method to use
	switch(sortType) {
		case 1:  // Insert sort
			cout << "\nINSERT SORT METHOD...\n";
			startSort = clock();  // Start sort time
			if(searchType == 1)
				wordsList.sortInsert();  // Sort
			break;
		case 2:  // Quick sort
			cout << "\nQUICK SORT METHOD...\n";
			startSort = clock();  // Start sort time
			if(searchType == 1)
				wordsList.sortQuick(0, wordsList.size() - 1);  // Sort
			break;
		case 3:  // Merge sort
			cout << "\nMERGE SORT METHOD...\n";
			startSort = clock();  // Start sort time
			if(searchType == 1)
				wordsList.sortMerge(0, wordsList.size() - 1);  // Sort
			break;
		case 4:  // Heap sort
			cout << "\nHEAP SORT METHOD...\n";
			startSort = clock();  // Start sort time
			if(searchType == 1)
				wordsList.sortHeap(wordsList.size());  // Sort
			break;
	}

	startFind = clock();  // Start time for finding words

	// Call find matches on word list (binary search) or hash table
	if (searchType == 1)
		findMatches(wordSearch, wordsList);
	else if (searchType == 1)
		findMatches(wordSearch, hashTab);

	// End time
	endTime = clock();

	// Print times
	printTime(startTime, startSort, startFind, endTime);

}

/*
   Main function operating on the following interpretation of the instructions:
   The main program will call each sorting method and search methodto demonstrate
   full functionality. Because the function search requires file input, the user
   will be expected to input a file name for each of the sorting methods. The
   time to process the word search will be displayed for each sorting method.
   The total time variable displayed includes the time taken to read in the
   grid from the file dictionary.txt.
*/
int main () {

	// Four types of sorting
	int insertSort = 1;
	int quickSort = 2;
	int mergeSort = 3;
	int heapSort = 4;

	// Two search types
	int binarySearch = 1;
	int hashTable = 2;

	try {
		// With binary search
		search<char>(insertSort, binarySearch);  // Insert
		search<char>(quickSort, binarySearch);  // Quick
		search<char>(mergeSort, binarySearch);  // Merge
		search<char>(heapSort, binarySearch);  // Merge

		// With hash table
		search<char>(insertSort, hashTable);  // Insert
		search<char>(quickSort, hashTable);  // Quick
		search<char>(mergeSort, hashTable);  // Merge
		search<char>(heapSort, hashTable);  // Merge
	}

	catch (const rangeError& re) {
		cerr << re.what() << endl;  // Output range error message
	}

	catch (const fileOpenError& re) {
		cerr << re.what() << endl;  // Output file error message
	}

    return 0;
}
